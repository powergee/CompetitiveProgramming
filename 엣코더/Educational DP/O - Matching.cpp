#include <iostream>
#include <vector>
#include <functional>
#define MOD 1000000007

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<std::vector<bool>> comp(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int v;
            std::cin >> v;
            comp[i][j] = v == 1;
        }
    }

    std::vector<std::vector<Long>> dp(n+1, std::vector<Long>(1<<n, -1));
    std::function<Long(int, int)> countCases = [&](int start, int used) -> Long {
        Long& result = dp[start][used];
        if (result != -1) {
            return result;
        }

        if (start == n) {
            return result = 1;
        }
        result = 0;
        for (int i = 0; i < n; ++i) {
            if (comp[start][i] && (used&(1<<i)) == 0) {
                result += countCases(start+1, used | (1<<i));
                result %= MOD;
            }
        }
        return result;
    };

    std::cout << countCases(0, 0);
    
    return 0;
}