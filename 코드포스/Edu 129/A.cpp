#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

void solve() {
    std::vector<int> cards[2];

    int n;
    std::cin >> n;
    cards[0].resize(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> cards[0][i];
    }
    std::sort(cards[0].begin(), cards[0].end());

    int m;
    std::cin >> m;
    cards[1].resize(m+1, 0);
    for (int i = 1; i <= m; ++i) {
        std::cin >> cards[1][i];
    }
    std::sort(cards[1].begin(), cards[1].end());

    std::vector<std::vector<std::vector<int>>> dp (n+2,
        std::vector<std::vector<int>>(m+2, 
            std::vector<int>(2, -1)
        )
    );

    std::function<int(int, int, int)> canWin = [&](int s1, int s2, int turn) -> int {
        if (dp[s1][s2][turn] != -1) {
            return dp[s1][s2][turn];
        }

        if (turn == 0) {
            for (int i = s1+1; i <= n; ++i) {
                if (cards[!turn][s2] < cards[turn][i] && !canWin(i, s2, !turn)) {
                    return dp[s1][s2][turn] = true;
                }
            }
        } else {
            for (int i = s2+1; i <= m; ++i) {
                if (cards[!turn][s1] < cards[turn][i] && !canWin(s1, i, !turn)) {
                    return dp[s1][s2][turn] = true;
                }
            }
        }

        return dp[s1][s2][turn] = false;
    };
    
    if (canWin(0, 0, 0)) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }

    if (canWin(0, 0, 1)) {
        std::cout << "Bob\n";
    } else {
        std::cout << "Alice\n";
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }
    return 0;
}