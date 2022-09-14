#include <iostream>

int A[500][1000];
int n;

void exchangeRows(int r1, int r2) {
    for (int i = 0; i < 2*n; ++i) {
        std::swap(A[r1][i], A[r2][i]);
    }
}

void subtractRows(int r1, int r2) {
    for (int i = 0; i < 2*n; ++i) {
        A[r1][i] -= A[r2][i];

        if (A[r1][i] < 0) {
            A[r1][i] = 1;
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Transpose
            scanf("%d", &A[j][i]);
        }
        A[i][i+n] = 1;
    }

    bool solvable = true;
    for (int i = 0; i < n; ++i) {
        if (A[i][i] == 0) {
            // 행교환이 필요.
            bool exchanged = false;
            for (int j = i+1; j < n; ++j) {
                if (A[j][i]) {
                    exchangeRows(i, j);
                    exchanged = true;
                    break;
                }
            }

            if (!exchanged) {
                solvable = false;
                break;
            }
        }

        for (int j = 0; j < n; ++j) {
            if (i == j || A[j][i] == 0) {
                continue;
            } else {
                subtractRows(j, i);
            }
        }
    }

    if (solvable) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[j][i+n]) {
                    printf("%d ", j+1);
                }
            }
            printf("\n");
        }
    } else {
        printf("-1");
    }

    return 0;
}