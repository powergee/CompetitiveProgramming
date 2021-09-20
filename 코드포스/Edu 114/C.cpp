#include <iostream>
#include <algorithm>
#include <numeric>

typedef long long Long;
Long heros[200000];

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", heros+i);
    }
    std::sort(heros, heros+n);
    Long sum = std::accumulate(heros, heros+n, 0LL);

    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        Long coins = 0;
        Long x, y;
        scanf("%lld %lld", &x, &y);
        auto attacker = std::lower_bound(heros, heros+n, x);

        if (attacker == heros+n) {
            coins += (x - heros[n-1]) + std::max(y - (sum - heros[n-1]), 0LL);
        } else {
            if (sum-*attacker < y) {
                Long case1 = y - (sum-*attacker); // 지금 선택된 유닛을 보내고, 나머지를 강화
                Long case2 = 0; // 지금 선택된 유닛의 이전을 보내고, 나머지를 필요하다면 강화
                if (attacker == heros) {
                    case2 = INT64_MAX;
                } else {
                    attacker--;
                    case2 += x - *attacker;
                    case2 += std::max(y - (sum - *attacker), 0LL);
                }
                coins += std::min(case1, case2);
            }
        }

        printf("%lld\n", coins);
    }

    return 0;
}