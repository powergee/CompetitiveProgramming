#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        int matrix[100][100];
        scanf("%d", &n);

        int val = 1;
        for (int r = 0; r < n; ++r) {
            for (int c = (r%2 ? 1 : 0); c < n; c += 2) {
                matrix[r][c] = val++;
            }
        }
        for (int r = 0; r < n; ++r) {
            for (int c = (r%2 ? 0 : 1); c < n; c += 2) {
                matrix[r][c] = val++;
            }
        }

        bool possible = true;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (r-1 > 0 && std::abs(matrix[r-1][c]-matrix[r][c]) == 1) {
                    possible = false;
                }
                if (r+1 < n && std::abs(matrix[r+1][c]-matrix[r][c]) == 1) {
                    possible = false;
                }
                if (c-1 > 0 && std::abs(matrix[r][c-1]-matrix[r][c]) == 1) {
                    possible = false;
                }
                if (c+1 < n && std::abs(matrix[r][c+1]-matrix[r][c]) == 1) {
                    possible = false;
                }
            }
        }

        if (possible)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    printf("%d ", matrix[i][j]);
                }
                printf("\n");
            }
        } else {
            printf("-1\n");
        }
    }

    return 0;
}