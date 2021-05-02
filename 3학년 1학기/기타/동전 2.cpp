#include <iostream>
#include <algorithm>

int main() {
    int n, k;
    int coins[100];
    int dp[10001];
    scanf("%d %d", &n, &k);

    std::fill(dp, dp+k+1, INT32_MAX);
    for (int i = 0; i < n; ++i) {
        scanf("%d", coins+i);
        if (coins[i] <= k) {
            dp[coins[i]] = 1;
        }
    }
    
    for (int v = 1; v <= k; ++v) {
        if (dp[v] == INT32_MAX) {
            continue;
        }

        for (int i = 0; i < n; ++i) {
            if (v+coins[i] <= k) {
                dp[v+coins[i]] = std::min(dp[v+coins[i]], dp[v]+1);
            }
        }
    }

    if (dp[k] == INT32_MAX) {
        printf("-1");
    } else {
        printf("%d", dp[k]);
    }

    return 0;
}