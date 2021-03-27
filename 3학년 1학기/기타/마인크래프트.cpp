#include <iostream>

int grid[500][500];

int main() {
    int n, m, b, sum = 0;
    scanf("%d %d %d", &n, &m, &b);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &grid[i][j]);
            sum += grid[i][j];
        }
    }
    sum += b;

    int ansTime = __INT32_MAX__, ansHeight = -1;
    int maxHeight = std::min(256, sum / (n*m));
    for (int h = 0; h <= maxHeight; ++h) {
        int time = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (h < grid[i][j]) {
                    time += (grid[i][j] - h) * 2;
                } else {
                    time += h - grid[i][j];
                }
            }
        }

        if (time <= ansTime) {
            ansTime = time;
            ansHeight = h;
        }
    }

    printf("%d %d", ansTime, ansHeight);
}