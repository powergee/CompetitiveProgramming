#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>

typedef long long Long;

int main() {
    Long n, k, x;
    scanf("%lld %lld %lld", &n, &k, &x);

    std::vector<Long> items;
    for (int i = 0; i < n; ++i) {
        Long value;
        scanf("%lld", &value);
        if (value >= x) {
            Long maxUse = value / x;
            Long actualUse = std::min(k, maxUse);
            k -= actualUse;
            value -= actualUse * x;
        }
        if (value > 0) {
            items.push_back(value);
        }
    }

    Long answer = 0;
    std::sort(items.begin(), items.end());
    for (int i = 0; i < int(items.size()) - k; ++i) {
        answer += items[i];
    }

    printf("%lld", answer);

    return 0;
}