#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <map>
#define MOD 1000000007LL

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    std::vector<std::vector<std::vector<Long>>> dp(n, std::vector<std::vector<Long>>(m, std::vector<Long>(3, -1)));

    std::function<Long(int, int, int)> countCases = [&](int r, int c, int need) -> Long {
        if (need == 3) {
            return 1;
        }
        if (r < 0 || r >= n || c < 0 || c >= m) {
            return 0;
        }
        Long& result = dp[r][c][need];
        if (result != -1) {
            return result;
        }

        result = (countCases(r+1, c, need) + countCases(r, c+1, need) - countCases(r+1, c+1, need) + MOD) % MOD;
        if (map[r][c] == "ESM"[need]) {
            result += countCases(r, c, need+1);
            result %= MOD;
        }
        return result;
    };

    std::cout << countCases(0, 0, 0);

    return 0;
}