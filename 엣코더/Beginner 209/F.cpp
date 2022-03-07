#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#define MOD 1000000007

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }
    
    std::vector<std::vector<int>> dp(n, std::vector<int>(n));
    dp[0][0] = 1;
    for (int i = 1; i < n; ++i) {
        int prevSum = 0;
        for (int j = 0; j <= i-1; ++j) {
            prevSum = (prevSum + dp[i-1][j]) % MOD;
        }
        int prevLowerSum = 0;
        int prevUpperSum = prevSum;

        for (int j = 0; j <= i; ++j) {
            dp[i][j] = 0;
            if (arr[i-1] == arr[i]) {
                dp[i][j] = (dp[i][j] + prevSum) % MOD;
            } else if (arr[i-1] < arr[i]) {
                dp[i][j] = (dp[i][j] + prevUpperSum) % MOD;
            } else {
                dp[i][j] = (dp[i][j] + prevLowerSum) % MOD;
            }
            prevLowerSum = (prevLowerSum + dp[i-1][j]) % MOD;
            prevUpperSum = (prevUpperSum - dp[i-1][j] + MOD) % MOD;
        }
    }

    int answer = 0;
    for (int j = 0; j < n; ++j) {
        answer = (answer + dp[n-1][j]) % MOD;
    }

    printf("%d", answer);

    return 0;
}