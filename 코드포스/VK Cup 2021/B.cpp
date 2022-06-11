#include <iostream>
#include <algorithm>

char map[20][21];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int h, w;
        scanf("%d %d", &h, &w);

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                map[i][j] = '0';
            }
            map[i][w] = '\0';
        }
        bool hEven = h % 2 == 0;
        bool wEven = w % 2 == 0;

        if (hEven && wEven) {
            for (int j = 1; j < w-1; j += 2) {
                map[0][j] = '1';
            }
            for (int i = 1; i < h-1; i += 2) {
                map[i][w-1] = '1';
            }
            for (int j = w-2; j > 0; j -= 2) {
                map[h-1][j] = '1';
            }
            for (int i = h-2; i > 0; i -= 2) {
                map[i][0] = '1';
            }
        } else if (!hEven && !wEven) {
            for (int j = 0; j < w; j += 2) {
                map[0][j] = '1';
            }
            for (int i = 0; i < h; i += 2) {
                map[i][w-1] = '1';
            }
            for (int j = w-1; j >= 0; j -= 2) {
                map[h-1][j] = '1';
            }
            for (int i = h-1; i >= 0; i -= 2) {
                map[i][0] = '1';
            }
        } else if (hEven && !wEven) {
            for (int j = 0; j < w-1; j += 2) {
                map[0][j] = '1';
            }
            for (int i = 1; i < h; i += 2) {
                map[i][w-1] = '1';
            }
            for (int j = w-1; j > 0; j -= 2) {
                map[h-1][j] = '1';
            }
            for (int i = h-2; i >= 0; i -= 2) {
                map[i][0] = '1';
            }
        } else if (!hEven && wEven) {
            for (int j = 1; j < w; j += 2) {
                map[0][j] = '1';
            }
            for (int i = 0; i < h-1; i += 2) {
                map[i][w-1] = '1';
            }
            for (int j = w-2; j >= 0; j -= 2) {
                map[h-1][j] = '1';
            }
            for (int i = h-1; i > 0; i -= 2) {
                map[i][0] = '1';
            }
        }

        for (int i = 0; i < h; ++i) {
            printf("%s\n", map[i]);
        }
        printf("\n");

    }

    return 0;
}