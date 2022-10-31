#include <iostream>
#include <vector>

using Long = long long;
const Long MOD = 100000007;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Long n;
    std::cin >> n;
    
    std::vector<Long> dp(n+1);
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i] = (2*i-1) * dp[i-1] + dp[i-2];
        dp[i] %= MOD;
    }
    std::cout << dp.back();

    return 0;
}