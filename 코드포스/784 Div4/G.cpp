#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        char map[n][m+1];
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
        }

        for (int j = 0; j < m; ++j) {
            int bottom = n-1, stones = 0;
            for (int i = n-1; i >= 0; --i) {
                if (map[i][j] == 'o') {
                    for (int k = bottom; k > i; --k) {
                        if (stones) {
                            map[k][j] = '*';
                            --stones;
                        } else {
                            map[k][j] = '.';
                        }
                    }
                    bottom = i-1;
                } else if (map[i][j] == '*') {
                    ++stones;
                }
            }
            for (int i = bottom; i >= 0; --i) {
                if (stones) {
                    map[i][j] = '*';
                    --stones;
                } else {
                    map[i][j] = '.';
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            printf("%s\n", map[i]);
        }
    }

    return 0;
}