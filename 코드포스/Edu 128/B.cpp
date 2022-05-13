#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<std::string> map(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> map[i];
        }

        std::pair<int, int> firstPos = {-1,-1};
        bool yes = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 'E') {
                    continue;
                }
                if (firstPos.first == -1) {
                    firstPos = { i, j };
                } else if (firstPos.first != i && firstPos.second > j) {
                    yes = false;
                }
            }
        }

        std::cout << (yes ? "YES\n" : "NO\n");
    }

    return 0;
}