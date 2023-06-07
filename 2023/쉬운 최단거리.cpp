#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    int map[n][m], dist[n][m];
    bool visited[n][m];
    int sr, sc;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            dist[r][c] = -1;
            visited[r][c] = false;
            std::cin >> map[r][c];
            if (map[r][c] == 2) {
                sr = r;
                sc = c;
            } else if (map[r][c] == 0) {
                dist[r][c] = 0;
            }
        }
    }

    std::queue<std::pair<int, int>> q;
    q.push({sr, sc});
    dist[sr][sc] = 0;
    visited[sr][sc] = true;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (auto [dr, dc] : std::vector<std::pair<int, int>>{
                 {-1, 0}, {1, 0}, {0, 1}, {0, -1}}) {
            int nr = dr + r;
            int nc = dc + c;
            if (0 <= nr && nr < n && 0 <= nc && nc < m && !visited[nr][nc] &&
                map[nr][nc] == 1) {
                visited[nr][nc] = true;
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            std::cout << dist[r][c] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}