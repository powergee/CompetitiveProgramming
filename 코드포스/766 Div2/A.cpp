#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, r, c;
        scanf("%d %d %d %d", &n, &m, &r, &c);

        bool blackExists = false;
        char map[n][m+1];
        for (int i = 0; i < n; ++i) {
            scanf("%s", map[i]);
            for (int j = 0; j < m; ++j) {
                blackExists |= map[i][j] == 'B';
            }
        }

        if (map[r-1][c-1] == 'B') {
            printf("0\n");
        } else if (!blackExists) {
            printf("-1\n");
        } else {
            bool straight = false;
            for (int i = 0; i < n; ++i) {
                straight |= map[i][c-1] == 'B';
            }
            for (int i = 0; i < m; ++i) {
                straight |= map[r-1][i] == 'B';
            }
            if (straight) {
                printf("1\n");
            } else {
                printf("2\n");
            }
        }
    }

    return 0;
}