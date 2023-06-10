#include <algorithm>
#include <iostream>
#include <string>

using std::size_t;

const int MOD = 10007;
int dp[1001][1001];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string input;
    std::cin >> input;

    for (size_t i = 0; i < input.size(); ++i) {
        dp[i][i] = 1;
    }
    for (size_t i = 0; i + 1 < input.size(); ++i) {
        dp[i][i + 1] = 2 + (input[i] == input[i + 1] ? 1 : 0);
    }
    for (size_t k = 2; k < input.size(); ++k) {
        for (size_t i = 0; i + k < input.size(); ++i) {
            size_t j = i + k;
            dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + MOD;
            if (input[i] == input[j]) {
                dp[i][j] += dp[i + 1][j - 1] + 1;
            }
            dp[i][j] %= MOD;
        }
    }
    std::cout << dp[0][input.size() - 1] << "\n";

    return 0;
}