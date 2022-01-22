#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<int> set(n);
    std::vector<bool> dp(k+1, false);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &set[i]);
    }

    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < n && set[j] <= i; ++j) {
            dp[i] = dp[i] || !dp[i-set[j]];
        }
    }
    printf(dp[k] ? "First" : "Second");

    return 0;
}