#include <iostream>
#include <algorithm>
#define MOD 1000000

int dp[1001][2][3];

int getAnswer(int remain, int late, int absent) {
    if (remain == 0) {
        return 1;
    }

    int& result = dp[remain][late][absent];
    if (result != -1) {
        return result;
    }

    result = getAnswer(remain-1, late, 0);

    if (late < 1) {
        result += getAnswer(remain-1, late+1, 0);
        result %= MOD;
    }

    if (absent < 2) {
        result += getAnswer(remain-1, late, absent+1);
        result %= MOD;
    }

    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(int), -1);
    printf("%d", getAnswer(n, 0, 0));

    return 0;
}