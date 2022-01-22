#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> deque(n);
    std::vector<std::vector<Long>> dp(n, std::vector<Long>(n, INT64_MIN));

    for (int i = 0; i < n; ++i) {
        scanf("%lld", &deque[i]);
    }

    std::function<Long(int, int)> getMaxDiff = [&](int left, int right) -> Long {
        Long& result = dp[left][right];
        if (result != INT64_MIN) {
            return result;
        }
        
        if (left == right) {
            return result = deque[left];
        }

        return result = std::max(deque[left]-getMaxDiff(left+1, right), deque[right]-getMaxDiff(left, right-1));
    };

    printf("%lld", getMaxDiff(0, n-1));

    return 0;
}