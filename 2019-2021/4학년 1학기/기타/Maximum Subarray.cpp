#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> dp(n, 0);
        scanf("%d", &dp[0]);
        for (int i = 1; i < n; ++i) {
            scanf("%d", &dp[i]);
            dp[i] += std::max(dp[i-1], 0);
        }

        printf("%d\n", *std::max_element(dp.begin(), dp.end()));
    }

    return 0;
}