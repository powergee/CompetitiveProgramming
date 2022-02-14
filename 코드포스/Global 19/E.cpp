#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        std::map<int, int> count;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            count[val]++;
        }

        std::map<int, std::vector<int>> valByCount;
        for (auto [val, cnt] : count) {
            valByCount[cnt].push_back(val);
        }
        for (auto& [cnt, vals] : valByCount) {
            std::sort(vals.begin(), vals.end(), std::greater<int>());
        }

        std::set<std::pair<int, int>> bad;
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            bad.emplace(u, v);
            bad.emplace(v, u);
        }

        Long answer = 0;
        for (int xCnt = 1; xCnt < n; ++xCnt) {
            for (int x : valByCount[xCnt]) {
                for (int yCnt = 1; yCnt <= xCnt; ++yCnt) {
                    for (int y : valByCount[yCnt]) {
                        if (x != y && bad.count({x, y}) == 0) {
                            answer = std::max(answer, Long(x+y)*(xCnt+yCnt));
                            break;
                        }
                    }
                }
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}