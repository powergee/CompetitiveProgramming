#include <iostream>

int map[2][100001];
int rowSum[2][100001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int m;
        scanf("%d", &m);

        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= m; ++j) {
                scanf("%d", &map[i][j]);
            }
        }

        for (int i = 0; i < 2; ++i) {
            for (int j = 1; j <= m; ++j) {
                rowSum[i][j] = rowSum[i][j-1] + map[i][j];
            }
        }

        int minScore = __INT32_MAX__;
        for (int i = 1; i <= m; ++i) {
            int score = std::max(
                rowSum[0][m] - rowSum[0][i],
                rowSum[1][i-1]
            );
            minScore = std::min(minScore, score);
        }
        printf("%d\n", minScore);
    }

    return 0;
}