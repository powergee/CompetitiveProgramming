#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

static const int dr[4] = { 0, 0, 1, -1 };
static const int dc[4] = { 1, -1, 0, 0 };

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

    auto updateMap = [&]() -> bool {
        bool changed = false;
        auto next = map;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (next[i][j] == 0) {
                    continue;
                }
                for (int k = 0; k < 4; ++k) {
                    int nr = i + dr[k];
                    int nc = j + dc[k];
                    if (0 <= nr && nr < n && 0 <= nc && nc < m && map[nr][nc] == 0) {
                        next[i][j] = 0;
                        changed = true;
                        break;
                    }
                }
            }
        }
        map = next;
        return changed;
    };
    
    std::cout << [&]() {
        for (int t = 1; updateMap(); ++t) {
            std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

            int count = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (visited[i][j] || map[i][j] == 0) {
                        continue;
                    }
                    ++count;
                    std::queue<std::pair<int, int>> q;
                    q.emplace(i, j);
                    visited[i][j] = true;
                    
                    while (q.size()) {
                        auto [r, c] = q.front();
                        q.pop();
                        for (int k = 0; k < 4; ++k) {
                            int nr = r + dr[k];
                            int nc = c + dc[k];
                            if (0 <= nr && nr < n && 0 <= nc && nc < n && !visited[nr][nc] && map[nr][nc] == 1) {
                                q.emplace(nr, nc);
                                visited[nr][nc] = true;
                            }
                        }
                    }
                }
            }

            if (count >= 2) {
                return t;
            }
        }
        return -1;
    }();

    return 0;
}