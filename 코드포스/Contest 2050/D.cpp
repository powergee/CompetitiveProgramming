#include <iostream>
#include <algorithm>
#include <queue>

const std::pair<int, int> DIRS[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m, k;
int horEdge[500][500];
int verEdge[500][500];
int dp[11][500][500];

int getCostBetween(std::pair<int, int> p1, std::pair<int, int> p2) {
    if (std::abs(p1.first - p2.first)) {
        int r = std::min(p1.first, p2.first);
        return verEdge[r][p1.second];
    } else {
        int c = std::min(p1.second, p2.second);
        return horEdge[p1.first][c];
    }
}

int getMinDist(int remain, int r, int c) {
    if (remain == 0) {
        return 0;
    }

    int& result = dp[remain][r][c];
    if (result != 0) {
        return result;
    }

    result = 1e9;
    for (int i = 0; i < 4; ++i) {
        int nr = r + DIRS[i].first;
        int nc = c + DIRS[i].second;
        if (0 <= nr && nr < n && 0 <= nc && nc < m) {
            result = std::min(result, getMinDist(remain-1, nr, nc)+2*getCostBetween({r, c}, {nr, nc}));
        }
    }

    return result;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m-1; ++j) {
            scanf("%d", &horEdge[i][j]);
        }
    }

    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &verEdge[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (k % 2) {
                printf("-1 ");
            } else {
                printf("%d ", getMinDist(k/2, i, j));
            }
        }
        printf("\n");
    }

    return 0;
}