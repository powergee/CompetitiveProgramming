#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;

        std::string goal;
        std::cin >> goal;

        bool possible = true;
        int l = 0;
        for (int i = 0; i < n; ++i) {
            if (goal[i] == 'W') {
                int r = i-1;
                if (l <= r) {
                    bool allSame = true;
                    for (int j = l; j <= r; ++j) {
                        if (goal[l] != goal[j]) {
                            allSame = false;
                            break;
                        }
                    }
                    if (allSame) {
                        possible = false;
                    }
                }
                l = i+1;
            }
        }

        if (l < n) {
            int r = n-1;
            if (l <= r) {
                bool allSame = true;
                for (int j = l; j <= r; ++j) {
                    if (goal[l] != goal[j]) {
                        allSame = false;
                        break;
                    }
                }
                if (allSame) {
                    possible = false;
                }
            }
        }

        if (possible) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}