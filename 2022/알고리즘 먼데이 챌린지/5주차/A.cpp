#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> map(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> map[i][j];
        }
    }

    auto findFood = [&](int i, int j) -> int {
        std::queue<std::tuple<int, int, int>> q;
        std::set<std::pair<int, int>> visited;
        q.emplace(i, j, 0);
        visited.emplace(i, j);

        while (q.size()) {
            auto [r, c, dist] = q.front();
            q.pop();
            if (map[r][c] == 2) {
                return 1;
            }
            if (dist >= m) {
                continue;
            }
            static const int dr[4] = { 0, 0, 1, -1 };
            static const int dc[4] = { 1, -1, 0, 0 };
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                if (0 <= nr && nr < n && 0 <= nc && nc < n && visited.count({nr, nc}) == 0) {
                    q.emplace(nr, nc, dist+1);
                    visited.emplace(nr, nc);
                }
            }
        }
        return 0;
    };

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] == 1) {
                answer += findFood(i, j);
            }
        }
    }

    std::cout << answer;

    return 0;
}