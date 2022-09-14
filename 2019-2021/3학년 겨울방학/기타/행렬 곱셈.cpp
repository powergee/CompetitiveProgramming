#include <iostream>

int main() {
    int n, m, k;
    scanf("%d %d", &n, &m);
    int mat1[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &mat1[i][j]);
        }
    }

    scanf("%d %d", &m, &k);
    int mat2[m][k];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            scanf("%d", &mat2[i][j]);
        }
    }

    int mat3[n][k];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            mat3[i][j] = 0;
            for (int d = 0; d < m; ++d) {
                mat3[i][j] += mat1[i][d] * mat2[d][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            printf("%d ", mat3[i][j]);
        }
        printf("\n");
    }

    return 0;
}