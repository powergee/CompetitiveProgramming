#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;
const Long MOD = Long(1e9)+7;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<int> bound(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &bound[i]);
    }

    std::vector<std::vector<Long>> dp(n, std::vector<Long>(k+1, 0));
    
    std::fill(dp[0].begin(), dp[0].begin()+bound[0]+1, 1);
    for (int i = 1; i < n; ++i) {
        std::vector<Long> prevSum(k+1, 0);
        prevSum[0] = dp[i-1][0];
        for (int j = 1; j <= k; ++j) {
            prevSum[j] = (prevSum[j-1] + dp[i-1][j]) % MOD;
        }
        for (int j = 0; j <= bound[i]; ++j) {
            dp[i][j] = prevSum[j];
        }
        for (int j = bound[i]+1; j <= k; ++j) {
            dp[i][j] = (prevSum[j] - prevSum[j-bound[i]-1] + MOD) % MOD;
        }
    }

    printf("%lld", dp[n-1][k]);

    return 0;
}