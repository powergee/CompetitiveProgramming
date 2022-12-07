#include <iostream>
#include <vector>
#include <functional>

static const int dr[4] { 0, 0, 1, -1 };
static const int dc[4] { 1, -1, 0, 0 };

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> map(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> map[i][j];
        }
    }

    int x, y, p;
    std::cin >> x >> y >> p;
    std::vector<std::vector<bool>> inStack(n, std::vector<bool>(m, false));

    std::function<int(int, int, int, int, int)> findMax = [&](int r, int c, int remain, int prevDr, int prevDc) -> int {
        if (remain == 0) {
            return 0;
        }
        inStack[r][c] = true;
        int nextMax = 0;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            int cost = (prevDr == dr[i] && prevDc == dc[i] ? 1 : 2);
            if (0 <= nr && nr < n && 0 <= nc && nc < m && !inStack[nr][nc] && remain >= cost) {
                nextMax = std::max(nextMax, findMax(nr, nc, remain-cost, dr[i], dc[i]));
            }
        }

        inStack[r][c] = false;
        return nextMax + map[r][c];
    };

    inStack[x][y] = true;
    int answer = map[x][y];
    for (int i = 0; i < 4; ++i) {
        int nr = x + dr[i];
        int nc = y + dc[i];
        if (0 <= nr && nr < n && 0 <= nc && nc < m) {
            answer = std::max(answer, map[x][y] + findMax(nr, nc, p, dr[i], dc[i]));
        }
    }

    std::cout << answer;

    return 0;
}