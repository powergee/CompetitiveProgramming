#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        std::vector<std::string> map(2);

        std::cin >> map[0];
        std::cin >> map[1];

        std::vector<int> entries;
        for (int c = 0; c < n; ++c) {
            if (map[0][c] == '*' || map[1][c] == '*') {
                entries.push_back(c);
            }
        }

        std::vector<std::vector<int>> dp(2, std::vector<int>(entries.size()));
        for (int currRow = 0; currRow < 2; ++currRow) {
            int e = int(entries.size())-1;
            int oppoRow = currRow ? 0 : 1;
            dp[currRow][e] = (map[oppoRow][entries[e]] == '*' ? 1 : 0);
        }

        for (int e = int(entries.size())-2; e >= 0; --e) {
            for (int currRow = 0; currRow < 2; ++currRow) {
                int c1 = entries[e];
                int c2 = entries[e+1];

                int oppoRow = currRow ? 0 : 1;
                if (map[oppoRow][c1] == '*') {
                    dp[currRow][e] = std::min(1 + (c2-c1) + dp[oppoRow][e+1], 1 + (c2-c1) + dp[currRow][e+1]);
                } else {
                    dp[currRow][e] = std::min((c2-c1) + dp[currRow][e+1], 1 + (c2-c1) + dp[oppoRow][e+1]);
                } 
            }
        }
        
        std::cout << std::min(dp[0][0], dp[1][0]) << "\n";
    }

    return 0;
}