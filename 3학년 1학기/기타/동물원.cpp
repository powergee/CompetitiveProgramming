#include <iostream>

enum { NONE, C1, C2 };

int main() {
    int n;
    scanf("%d", &n);

    int dp[3][n+1];
    dp[NONE][0] = 1;
    dp[C1][0] = dp[C2][0] = 0;

    for (int i = 1; i <= n; ++i) {
        dp[NONE][i] = (dp[NONE][i-1] + dp[C1][i-1] + dp[C2][i-1]) % 9901;
        dp[C1][i] = (dp[NONE][i-1] + dp[C2][i-1]) % 9901;
        dp[C2][i] = (dp[NONE][i-1] + dp[C1][i-1]) % 9901;
    }

    printf("%d", (dp[NONE][n] + dp[C1][n] + dp[C2][n]) % 9901);

    return 0;
}