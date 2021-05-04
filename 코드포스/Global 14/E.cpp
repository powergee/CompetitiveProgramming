#include <iostream>

using Long = long long;

int main() {
    int n;
    Long m, singleDp[401], totalDp[401][401], combDp[401][401];
    scanf("%d %lld", &n, &m);

    Long power = 1;
    singleDp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        singleDp[i] = power % m;
        power *= 2;
        power %= m;
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i < j) {
                combDp[i][j] = 0;
            } else if (j == 0) {
                combDp[i][j] = 1;
            } else {
                combDp[i][j] = (combDp[i-1][j-1] + combDp[i-1][j]) % m;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        totalDp[i][i] = singleDp[i];
        for (int j = 0; j < i; ++j) {
            totalDp[i][j] = 0;
            for (int k = 1; k <= j; ++k) {
                totalDp[i][j] += ((singleDp[k] * totalDp[i-k-1][j-k]) % m * combDp[j][k]) % m;
                totalDp[i][j] %= m;
            }
        }
    }

    Long answer = 0;
    for (int i = 1; i <= n; ++i) {
        answer += totalDp[n][i];
        answer %= m;
    }
    printf("%lld", answer);

    return 0;
}