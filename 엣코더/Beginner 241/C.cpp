#include <iostream>
#include <string>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    bool possible = false;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // -
            if (j+5 < n) {
                int count = 0;
                for (int d = 0; d < 6; ++d) {
                    if (map[i][j+d] == '#') {
                        ++count;
                    }
                }
                if (count >= 4) {
                    possible = true;
                }
            }

            // |
            if (i+5 < n) {
                int count = 0;
                for (int d = 0; d < 6; ++d) {
                    if (map[i+d][j] == '#') {
                        ++count;
                    }
                }
                if (count >= 4) {
                    possible = true;
                }
            }

            // '/'
            if (0 <= i-5 && j+5 < n) {
                int count = 0;
                for (int d = 0; d < 6; ++d) {
                    if (map[i-d][j+d] == '#') {
                        ++count;
                    }
                }
                if (count >= 4) {
                    possible = true;
                }
            }

            // '\'
            if (i+5 < n && j+5 < n) {
                int count = 0;
                for (int d = 0; d < 6; ++d) {
                    if (map[i+d][j+d] == '#') {
                        ++count;
                    }
                }
                if (count >= 4) {
                    possible = true;
                }
            }
        }
    }

    printf(possible ? "Yes" : "No");

    return 0;
}