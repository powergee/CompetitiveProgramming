#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <tuple>
#include <functional>
#define MOD 1000000007LL

typedef long long Long;

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        Long pow = getModPow(val, exp/2);
        return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
    }
}

Long getModInverse(Long val) {
    return getModPow(val, MOD-2);
}

void solve() {
    int n;
    std::cin >> n;
    std::string word;
    std::cin >> word;

    std::vector<Long> fact(n+1, 1);
    for (int i = 1; i <= n; ++i) {
        fact[i] *= fact[i-1] * i;
        fact[i] %= MOD;
    }

    std::vector<std::vector<std::vector<Long>>> dp(n, std::vector<std::vector<Long>>(n, std::vector<Long>(n+1, -1)));

    std::function<Long(int, int, int)> countCandies = [&](int i, int j, int l) -> Long {
        if (l == 0) {
            return 1;
        } else if (l < 0 || i > j || j-i+1 < l) {
            return 0;
        } else if (l == 1) {
            return j-i+1;
        } else if (dp[i][j][l] != -1) {
            return dp[i][j][l];
        } else if (word[i] == word[j]) {
            return dp[i][j][l] = (countCandies(i+1, j-1, l-2) + countCandies(i, j-1, l) + countCandies(i+1, j, l) - countCandies(i+1, j-1, l) + MOD) % MOD;
        } else {
            return dp[i][j][l] = (countCandies(i, j-1, l) + countCandies(i+1, j, l) - countCandies(i+1, j-1, l) + MOD) % MOD;
        }
    };

    Long p = fact[n];
    for (int l = 1; l < n; ++l) {
        p += (((countCandies(0, n-1, l) * fact[l]) % MOD) * fact[n-l]) % MOD;
        p %= MOD;
    }
    Long q = fact[n];
    std::cout << (p * getModInverse(q)) % MOD << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}