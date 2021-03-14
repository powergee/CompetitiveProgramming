#include <iostream>
#include <algorithm>

int enemies[2][10001];
int dpEqual[4][10001];
int dpUpper[4][10001];
int dpLower[4][10001];
int n, w;

void fillDpArray(int k, int first, int last) {
    for (int i = first; i <= last; ++i) {
        int c[4];
        std::fill(c, c+4, INT32_MAX);

        // dpUpper
        c[0] = dpEqual[k][i-1] + 1;
        if (enemies[0][i-1] + enemies[0][i] <= w) {
            c[1] = dpLower[k][i-1] + 1;
        }
        dpUpper[k][i] = std::min(c[0], c[1]);
        
        // dpLower
        c[0] = c[1] = INT32_MAX;
        c[0] = dpEqual[k][i-1] + 1;
        if (enemies[1][i-1] + enemies[1][i] <= w) {
            c[1] = dpUpper[k][i-1] + 1;
        }
        dpLower[k][i] = std::min(c[0], c[1]);

        // dpEqual
        c[0] = c[1] = INT32_MAX;
        if (enemies[0][i-1] + enemies[0][i] <= w && enemies[1][i-1] + enemies[1][i] <= w) {
            c[0] = dpEqual[k][i-2] + 2;
        }

        if (enemies[0][i] + enemies[1][i] <= w) {
            c[1] = dpEqual[k][i-1] + 1;
        }

        c[2] = dpUpper[k][i] + 1;
        c[3] = dpLower[k][i] + 1;

        dpEqual[k][i] = *std::min_element(c, c+4);
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &n, &w);

        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= n; ++j) {
                scanf("%d", &enemies[i][j]);
            }
        }

        int result = INT32_MAX;

        for (int k = 0; k < 4; ++k) {
            switch (k)
            {
            case 0:
                if (enemies[0][1] + enemies[1][1] <= w) {
                    dpEqual[k][1] = 1;
                } else {
                    dpEqual[k][1] = 2;
                }
                dpUpper[k][1] = dpLower[k][1] = 1;
                fillDpArray(k, 2, n);
                result = std::min(result, dpEqual[k][n]);
                break;

            case 1:
                if (n < 2 || w < enemies[0][1] + enemies[0][n]) {
                    continue;
                }
                dpEqual[k][1] = 1;
                dpUpper[k][1] = 0;
                dpLower[k][1] = 1;
                
                if (enemies[0][2] + enemies[1][2] <= w) {
                    dpEqual[k][2] = 2;
                } else if (enemies[1][1] + enemies[1][2] <= w) {
                    dpEqual[k][2] = 2;
                } else {
                    dpEqual[k][2] = 3;
                }

                dpUpper[k][2] = 2;
                
                if (enemies[1][1] + enemies[1][2] <= w) {
                    dpLower[k][2] = 1;
                } else {
                    dpLower[k][2] = 2;
                }

                fillDpArray(k, 3, n);
                result = std::min(result, dpLower[k][n] + 1);
                break;

            case 2:
                if (n < 2 || w < enemies[1][1] + enemies[1][n]) {
                    continue;
                }
                dpEqual[k][1] = 1;
                dpUpper[k][1] = 1;
                dpLower[k][1] = 0;

                if (enemies[0][2] + enemies[1][2] <= w) {
                    dpEqual[k][2] = 2;
                } else if (enemies[0][1] + enemies[0][2] <= w) {
                    dpEqual[k][2] = 2;
                } else {
                    dpEqual[k][2] = 3;
                }

                if (enemies[0][1] + enemies[0][2] <= w) {
                    dpUpper[k][2] = 1;
                } else {
                    dpUpper[k][2] = 2;
                }

                dpLower[k][2] = 2;

                fillDpArray(k, 3, n);
                result = std::min(result, dpUpper[k][n] + 1);
                break;

            case 3:
                if (n < 2 || w < enemies[0][1] + enemies[0][n] || w < enemies[1][1] + enemies[1][n]) {
                    continue;
                }

                dpEqual[k][1] = dpUpper[k][1] = dpLower[k][1] = 0;

                if (enemies[0][2] + enemies[1][2] <= w) {
                    dpEqual[k][2] = 1;
                } else {
                    dpEqual[k][2] = 2;
                }

                dpUpper[k][2] = dpLower[k][2] = 1;

                fillDpArray(k, 3, n-1);
                result = std::min(result, dpEqual[k][n-1] + 2);
                break;
            }
        }

        printf("%d\n", result);
    }

    return 0;
}