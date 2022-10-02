#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>
#include <cassert>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    
    int k;
    std::cin >> k;

    std::vector<std::vector<int>> leftBound(n+1, std::vector<int>(m+1, 0));
    std::vector<std::vector<int>> upperBound(n+1, std::vector<int>(m+1, 0));
    for (int i = 0; i < k; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        --a, --b, --c, --d;
        leftBound[a][b]++;
        leftBound[c+1][b]--;
        upperBound[a][b]++;
        upperBound[a][d+1]--;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            upperBound[i][j] += upperBound[i][j-1];
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 1; i < n; ++i) {
            leftBound[i][j] += leftBound[i-1][j];
        }
    }
    
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    for (int i = n-1; i >= 0; --i) {
        for (int j = m-1; j >= 0; --j) {
            if (i == n-1 && j == m-1) {
                dp[i][j] = 0;
                continue;
            }

            int cands[2] = { INT32_MAX, INT32_MAX };
            if (j+1 < m) {
                cands[0] = dp[i][j+1] + leftBound[i][j+1];
            }
            if (i+1 < n) {
                cands[1] = dp[i+1][j] + upperBound[i+1][j];
            }
            dp[i][j] = std::min(cands[0], cands[1]);
        }
    }

    std::cout << upperBound[0][0] + dp[0][0];

    return 0;
}