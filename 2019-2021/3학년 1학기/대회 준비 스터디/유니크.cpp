#include <iostream>

int a[200][3];
int score[200];
int memo[3][101];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", &a[i][0], &a[i][1], &a[i][2]);
        memo[0][a[i][0]]++;
        memo[1][a[i][1]]++;
        memo[2][a[i][2]]++;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (memo[j][a[i][j]] == 1) {
                score[i] += a[i][j];
            }
        }
        printf("%d\n", score[i]);
    }

    return 0;
}