#include <iostream>
#include <algorithm>
#define MOD 998244353

typedef long long Long;

std::pair<int, int> nums[5000];
Long dp[5000][5001];

Long countCombOfSum(int right, int bound) {
    if (right == -1) {
        return (0 <= bound ? 1 : 0);
    }

    Long& result = dp[right][bound];
    if (result != -1) {
        return result;
    }
    result = countCombOfSum(right-1, bound);
    if (nums[right].second <= bound) {
        result += countCombOfSum(right-1, bound-nums[right].second);
        result %= MOD;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i].first);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &nums[i].second);
    }

    std::sort(nums, nums+n);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1LL);

    Long result = (nums[0].second <= nums[0].first ? 1 : 0);
    for (int i = 1; i < n; ++i) {
        if (nums[i].second <= nums[i].first) {
            result += countCombOfSum(i-1, nums[i].first-nums[i].second);
            result %= MOD;
        }
    }
    printf("%lld", result);

    return 0;
}