#include <iostream>
#include <vector>
#include <map>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int map[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    #define isValid(r, c) (0 <= (r) && (r) < n && 0 <= (c) && (c) < m)
    static const int dr[4] { 0, 0, 1, -1 };
    static const int dc[4] { 1, -1, 0, 0 };

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 0) {
                continue;
            }

            for (int k = 0; k < 4; ++k) {
                int nr = i+dr[k];
                int nc = j+dc[k];
                if (isValid(nr, nc) && map[nr][nc] == 0) {
                    edges.emplace_back(i, j);
                    break;
                }
            }
        }
    }

    while (k--) {
        std::map<int, std::map<int, int>> assigned;
        auto update = [&](int r, int c, int color) {
            if (assigned.find(r) == assigned.end()) {
                assigned[r] = std::map<int, int>();
            }
            if (assigned[r].find(c) == assigned[r].end()) {
                assigned[r][c] = color;
            } else {
                assigned[r][c] = std::min(color, assigned[r][c]);
            }
        };

        for (auto [r, c] : edges) {
            for (int k = 0; k < 4; ++k) {
                int nr = r+dr[k];
                int nc = c+dc[k];
                if (isValid(nr, nc) && map[nr][nc] == 0) {
                    update(nr, nc, map[r][c]);
                }
            }
        }

        edges.clear();
        for (const auto& [r, sub] : assigned) {
            for (const auto& [c, color] : sub) {
                map[r][c] = color;
                for (int k = 0; k < 4; ++k) {
                    int nr = r+dr[k];
                    int nc = c+dc[k];
                    if (isValid(nr, nc) && map[nr][nc] == 0) {
                        edges.emplace_back(r, c);
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        printf("%d", map[i][0]);
        for (int j = 1; j < m; ++j) {
            printf(" %d", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}