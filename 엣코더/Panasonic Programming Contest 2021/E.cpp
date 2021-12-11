#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
#include <iostream>
#include <vector>
#include <map>

typedef long long Long;

int main() {
    Long n, x;
    scanf("%lld %lld", &n, &x);
    std::vector<Long> coins(n);
    
    for (int i = 0; i < n; ++i) {
        Long c;
        scanf("%lld", &c);
        coins[i] = c;
    }

    std::function<Long(Long, int)> getMinCost;
    getMinCost = [&](Long total, int cIdx) -> Long {
        static std::map<std::pair<Long, int>, Long> dp;
        if (total == 0) {
            return 0;
        }
        if (cIdx == n-1) {
            return total / coins[cIdx];
        }

        std::pair<Long, int> bucket(total, cIdx);
        if (dp.find(bucket) != dp.end()) {
            return dp[bucket];
        }

        std::vector<Long> cands;
        // Pay all
        Long naiveCount = (total % coins[cIdx+1]) / coins[cIdx];
        cands.push_back(naiveCount + getMinCost(total-naiveCount*coins[cIdx], cIdx+1));

        // Pay more
        Long revCount = (coins[cIdx+1]/coins[cIdx]) - naiveCount;
        cands.push_back(revCount + getMinCost(total-naiveCount*coins[cIdx]+coins[cIdx+1], cIdx+1));

        return dp[bucket] = *std::min_element(cands.begin(), cands.end());
    };

    printf("%lld", getMinCost(x, 0));
    return 0;
}
