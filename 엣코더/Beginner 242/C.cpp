#include <iostream>
#include <algorithm>
#include <vector>
#define MOD 998244353

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<Long>> dp(n+1, std::vector<Long>(10, 0));
    for (int v = 1; v <= 9; ++v) {
        dp[0][v] = 1LL;
    }

    for (int i = 1; i < n; ++i) {
        for (int v = 1; v <= 9; ++v) {
            dp[i][v] += dp[i-1][v];
            if (v > 1) {
                dp[i][v] += dp[i-1][v-1];
            }
            if (v < 9) {
                dp[i][v] += dp[i-1][v+1];
            }
            dp[i][v] %= MOD;
        }
    }

    Long answer = 0;
    for (int v = 1; v <= 9; ++v) {
        answer += dp[n-1][v];
        answer %= MOD;
    }
    printf("%lld", answer);

    return 0;
}