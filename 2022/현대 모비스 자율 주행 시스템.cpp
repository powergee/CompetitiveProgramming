#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    std::cin >> n >> m >> k;

    int map[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> map[i][j];
        }
    }

    std::vector<std::tuple<int, int, int>> moves = {
        { 0, 1, 0 },
        { 0, -1, 0 },
        { 1, 0, 0 },
        { -1, 0, 0 },
    };
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            int active;
            std::cin >> active;
            if (active) {
                moves.emplace_back(i, j, 1);
            }
        }
    }

    std::queue<std::tuple<int, int, int, bool>> q;
    int dist[n][m][k+1][2];
    std::fill(&dist[0][0][0][0], &dist[0][0][0][0] + sizeof(dist) / sizeof(int), INT32_MAX);
    q.emplace(0, 0, 0, false);
    dist[0][0][0][0] = 0;
    
    while (q.size()) {
        auto [r, c, used, passed] = q.front();
        q.pop();

        if (r == n-1 && c == m-1 && passed) {
            break;
        }

        for (auto [dr, dc, cost] : moves) {
            int nr = r+dr;
            int nc = c+dc;
            int newUsed = used+cost;
            bool newPassed = passed || map[nr][nc] == 2;
            if (newUsed <= k && 
                0 <= nr && nr < n && 0 <= nc && nc < m && 
                dist[nr][nc][newUsed][newPassed] == INT32_MAX &&
                map[nr][nc] != 1
            ) {
                dist[nr][nc][newUsed][newPassed] = dist[r][c][used][passed] + 1;
                q.emplace(nr, nc, newUsed, newPassed);
            }
        }
    }

    int answer = INT32_MAX;
    for (int used = 0; used <= k; ++used) {
        answer = std::min(answer, dist[n-1][m-1][used][true]);
    }

    if (answer == INT32_MAX) {
        std::cout << -1;
    } else {
        std::cout << answer;
    }

    return 0;
}