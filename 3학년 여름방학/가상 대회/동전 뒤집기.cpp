#include <iostream>
#include <algorithm>

char flip(char c) {
    return c == 'H' ? 'T' : 'H';
}

int main() {
    int n;
    char coins[20][21];
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%s", coins[i]);
    }

    int answer = __INT32_MAX__;
    char newCoins[20][21];
    for (int rowMask = 0; rowMask < (1<<n); ++rowMask) {
        int rowHeadCount[20];

        for (int i = 0; i < n; ++i) {
            rowHeadCount[i] = 0;
            for (int j = 0; j < n; ++j) {
                newCoins[i][j] = ((rowMask & (1<<j)) ? flip(coins[i][j]) : coins[i][j]);
                rowHeadCount[i] += (newCoins[i][j] == 'H' ? 1 : 0);
            }
        }

        int totalHeadCount = 0;
        for (int i = 0; i < n; ++i) {
            totalHeadCount += std::max(rowHeadCount[i], n - rowHeadCount[i]);
        }
        answer = std::min(answer, n*n-totalHeadCount);
    }

    printf("%d", answer);
    return 0;
}