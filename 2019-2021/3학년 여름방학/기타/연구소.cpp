#include <iostream>
#include <queue>
#include <algorithm>

int n, m;
int map[8][8];
bool visited[8][8];

int getCompSize() {
    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 2) {
                q.emplace(i, j);
            }
            visited[i][j] = false;
        }
    }

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        if (visited[curr.first][curr.second]) {
            continue;
        }
        visited[curr.first][curr.second] = true;

        static const int dr[4] = { 0, 0, 1, -1 };
        static const int dc[4] = { 1, -1, 0, 0 };
        for (int i = 0; i < 4; ++i) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];

            if (0 <= nr && nr < n && 0 <= nc && nc < m && !visited[nr][nc] && map[nr][nc] != 1) {
                q.emplace(nr, nc);
            }
        }
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (visited[i][j]) {
                ++result;
            }
        }
    }

    return result;
}

int main() {
    scanf("%d %d", &n, &m);

    int wallCount = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
            if (map[i][j] == 1) {
                ++wallCount;
            }
        }
    }

    int minComp = INT32_MAX;
    for (int i = 0; i < n*m; ++i) {
        for (int j = 0; j < n*m; ++j) {
            for (int k = 0; k < n*m; ++k) {
                if (map[i/m][i%m] == 0 && map[j/m][j%m] == 0 && map[k/m][k%m] == 0) {
                    map[i/m][i%m] = 1;
                    map[j/m][j%m] = 1;
                    map[k/m][k%m] = 1;
                    minComp = std::min(getCompSize(), minComp);
                    map[i/m][i%m] = 0;
                    map[j/m][j%m] = 0;
                    map[k/m][k%m] = 0;
                }
            }
        }
    }

    printf("%d", n*m-wallCount-minComp-3);

    return 0;
}