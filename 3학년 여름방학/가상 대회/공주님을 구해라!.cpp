#include <iostream>
#include <queue>
#include <algorithm>
#define INF (__INT32_MAX__/2)

int map[100][100];
int dist[100][100];

int main() {
    int n, m, t;
    scanf("%d %d %d", &n, &m, &t);

    std::pair<int, int> sword;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
            if (map[i][j] == 2) {
                sword = {i, j};
            }
        }
    }

    std::fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(int), INF);
    std::queue<std::pair<int, int>> q;
    dist[0][0] = 0;
    q.emplace(0, 0);

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        int r = curr.first / m;
        int c = curr.first % m;

        const static int dr[4] = { 0, 0, 1, -1 };
        const static int dc[4] = { -1, 1, 0, 0 };
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (0 <= nr && nr < n && 0 <= nc && nc < m && dist[nr][nc] == INF && map[nr][nc] != 1) {
                dist[nr][nc] = curr.second + 1;
                q.emplace(nr*m + nc, curr.second + 1);
            }
        }
    }
    
    int case1 = dist[n-1][m-1];
    int case2 = dist[sword.first][sword.second] + (n-1 - sword.first) + (m-1 - sword.second);

    int answer = std::min(case1, case2);

    if (answer >= INF || answer > t) {
        printf("Fail");
    } else {
        printf("%d", answer);
    }

    return 0;
}