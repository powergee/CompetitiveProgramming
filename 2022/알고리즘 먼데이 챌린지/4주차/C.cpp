#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    if (n == 1) {
        std::cout << 5;
        return 0;
    }

    const Long MOD = 100000007;

    auto isValid = [&](int prev, int curr) {
        for (int e = 0; e < 2; ++e) {
            if (((prev&(1<<e)) && (prev&(1<<(e+1)))) || ((curr&(1<<e)) && (curr&(1<<(e+1))))) {
                return false;
            }
        }
        for (int e = 0; e < 3; ++e) {
            if ((prev&(1<<e)) && (curr&(1<<e))) {
                return false;
            }
        }
        return true;
    };

    Long dp[n][1<<3];
    for (int prev = 0; prev < (1<<3); ++prev) {
        dp[n-1][prev] = 1;
    }

    for (int i = n-2; i >= 0; --i) {
        for (int prev = 0; prev < (1<<3); ++prev) {
            dp[i][prev] = 0;
            for (int curr = 0; curr < (1<<3); ++curr) {
                if (isValid(prev, curr)) {
                    dp[i][prev] += dp[i+1][curr];
                    dp[i][prev] %= MOD;
                }
            }
        }
    }

    Long answer = 0;
    for (int prev = 0; prev < (1<<3); ++prev) {
        answer += dp[0][prev];
        answer %= MOD;
    }
    std::cout << answer;

    return 0;
}