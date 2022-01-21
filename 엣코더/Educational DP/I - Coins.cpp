#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<double> p(n+1);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf", &p[i]);
    }

    std::vector<std::vector<double>> dp(n+1, std::vector<double>(n+1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] = p[i]*dp[i-1][j-1] + (1-p[i])*dp[i-1][j];
        }
    }

    double sum = 0;
    for (int i = n; n-i < i; --i) {
        sum += dp[n][i];
    }
    printf("%.10lf", sum);

    return 0;
}