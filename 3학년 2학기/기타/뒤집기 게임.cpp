#include <iostream>

int main() {
    int n;
    scanf("%d", &n);
    bool origin[n][n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val;
            scanf("%d", &val);
            origin[i][j] = val ? true : false;
        }
    }

    int answer = INT32_MAX;
    for (int rowInv = 0; rowInv < (1<<n); ++rowInv) {
        for (int colInv = 0; colInv < (1<<n); ++colInv) {
            int map[n][n];
            std::copy(&origin[0][0], &origin[0][0]+n*n, &map[0][0]);
            int lineFlip = 0;
            for (int r = 0; r < n; ++r) {
                if (rowInv & (1<<r)) {
                    ++lineFlip;
                    for (int c = 0; c < n; ++c) {
                        map[r][c] = !map[r][c];
                    }
                }
            }
            for (int c = 0; c < n; ++c) {
                if (colInv & (1<<c)) {
                     ++lineFlip;
                    for (int r = 0; r < n; ++r) {
                        map[r][c] = !map[r][c];
                    }
                }
            }
            int cellFlip = 0;
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < n; ++c) {
                    cellFlip += (map[r][c] ? 1 : 0);
                }
            }
            answer = std::min(answer, lineFlip + std::min(cellFlip, n*n-cellFlip));
        }
    }

    printf("%d", answer);

    return 0;
}