#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> slimes(n), sum(n, 0);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &slimes[i]);
    }

    sum[0] = slimes[0];
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + slimes[i];
    }

    std::vector<std::vector<Long>> dp(n, std::vector<Long>(n, INT64_MAX));

    auto getSum = [&](int left, int right) -> Long {
        if (left == 0) {
            return sum[right];
        }
        return sum[right] - sum[left-1];
    };

    std::function<Long(int, int)> getMinCost = [&](int left, int right) -> Long {
        Long& result = dp[left][right];
        if (result != INT64_MAX) {
            return result;
        }

        if (left == right) {
            return result = 0;
        }

        for (int mid = left; mid < right; ++mid) {
            result = std::min(result, getMinCost(left, mid) + getMinCost(mid+1, right) + getSum(left, right));
        }
        return result;
    };

    printf("%lld", getMinCost(0, n-1));

    return 0;
}