#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        char map[10][20];
        bool filled[10][20] = {};

        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
        }

        auto tryToFill = [&](int r, int c, int d) -> bool {
            for (int i = 0; i <= d; ++i) {
                if (map[r-i][c-i] == '.' || map[r-i][c+i] == '.') {
                    return false;
                }
            }
            for (int i = 0; i <= d; ++i) {
                filled[r-i][c-i] = filled[r-i][c+i] = true;
            }
            return true;
        };

        for (int d = k; d+1 <= n && 2*d+1 <= m; ++d) {
            for (int i = d; i < n; ++i) {
                for (int j = d; j+d < m; ++j) {
                    tryToFill(i, j, d);
                }
            }
        }

        bool yes = true;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((map[i][j] == '*') != filled[i][j]) {
                    yes = false;
                }
            }
        }

        if (yes) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}