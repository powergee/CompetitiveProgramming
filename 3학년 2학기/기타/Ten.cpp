#include <iostream>

int map[301][301];
int sum[301][301];

int countSubRect(int r, int c) {
    int count = 0;
    for (int i = r; i > r-10 && i > 0; --i) {
        for (int j = c; j > c-10 && j > 0; --j) {
            if (sum[r][c] - sum[i-1][c] - sum[r][j-1] + sum[i-1][j-1] == 10) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    int row, col;
    scanf("%d %d", &row, &col);

    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            scanf("%d", &map[row][col]);
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + map[row][col];
        }
    }

    int answer = 0;
    for (int i = 1; i <= row; ++i) {
        for (int j = 1; j <= col; ++j) {
            answer += countSubRect(i, j);
        }
    }

    printf("%d", answer);

    return 0;
}