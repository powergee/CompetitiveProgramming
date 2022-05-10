#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        int matrix[n][m];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &matrix[i][j]);
            }
        }

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int curr = 0;
                for (int r = 0; r < n; ++r) { // '/'
                    // r+c == i+j
                    int c = i+j-r;
                    if (0 <= c && c < m) {
                        curr += matrix[r][c];
                    }
                }
                for (int r = 0; r < n; ++r) { // '\'
                    // r-c == i-j
                    int c = r-i+j;
                    if (0 <= c && c < m) {
                        curr += matrix[r][c];
                    }
                }
                curr -= matrix[i][j];
                answer = std::max(answer, curr);
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}