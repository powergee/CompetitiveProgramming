#include <iostream>
#include <vector>

typedef long long Long;

Long sum[200001];
Long dp[200001];

int main() {
    Long n, m;
    std::cin >> n >> m;

    dp[1] = 1; sum[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = sum[i-1];

        Long d;
        for (d = 2; d*d <= i; ++d) {
            dp[i] += dp[i/d];
            dp[i] %= m;
        }
        int q = i/d;
        for (int q = i/d; q >= 1; --q) {
            std::pair<int, int> dRange = { i/(q+1), i/q };
            dp[i] += (dRange.second-dRange.first) * dp[q];
            dp[i] %= m;
        }

        sum[i] = (dp[i] + sum[i-1]) % m;
    }

    std::cout << dp[n];

    return 0;
}