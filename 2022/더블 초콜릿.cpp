#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <queue>
#include <cassert>

int main() {
    const int dr[] { 0, 0, 1, -1 };
    const int dc[] { 1, -1, 0, 0 };
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> color(n, std::vector<int>(n));
    std::vector<std::vector<int>> number(n, std::vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> color[i][j];
        }
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int r, c, k;
        std::cin >> r >> c >> k;
        number[r-1][c-1] = k;
    }

    std::vector<std::string> rawMap(2*n+1);
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    for (int i = 0; i < 2*n+1; ++i) {
        std::cin >> rawMap[i];
    }

    auto getCoord = [&](int r, int c) {
        return std::make_pair(1+2*r, 1+2*c);
    };

    auto isConnected = [&](int r, int c, int dr, int dc) {
        assert((dr == 0 && std::abs(dc) == 1) || (std::abs(dr) == 1 && dc == 0));
        auto [r1, c1] = getCoord(r, c);
        auto [r2, c2] = getCoord(r+dr, c+dc);
        return rawMap[(r1+r2)/2][(c1+c2)/2] == '.';
    };

    auto getComp = [&](int r, int c) {
        std::vector<std::pair<int, int>> comp;
        std::queue<std::pair<int, int>> q;

        visited[r][c] = true;
        q.emplace(r, c);
        comp.emplace_back(r, c);

        while (q.size()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (int i = 0; i < 4; ++i) {
                int nr = r+dr[i];
                int nc = c+dc[i];
                if (0 <= nr && nr < n && 0 <= nc && nc < n && !visited[nr][nc] && isConnected(r, c, dr[i], dc[i])) {
                    q.emplace(nr, nc);
                    comp.emplace_back(nr, nc);
                    visited[nr][nc] = true;
                }
            }
        }
        return comp;
    };

    std::vector<std::vector<std::pair<int, int>>> comps;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!visited[i][j]) {
                comps.emplace_back(getComp(i, j));
            }
        }
    }

    std::cout << [&]() -> int {
        for (const auto& comp : comps) {
            using Group = std::vector<std::pair<int, int>>;
            Group group[2];
            int num = -1;
            for (auto [i, j] : comp) {
                group[color[i][j]].emplace_back(i, j);
                if (number[i][j] != -1) {
                    if (num != -1) {
                        return 0;
                    } else {
                        num = number[i][j];
                    }
                }
            }
            if (group[0].size() != group[1].size()) {
                return 0;
            }
            if (num != -1 && group[0].size() != num) {
                return 0;
            }

            auto areConnected = [&](const Group& g) {
                std::vector<bool> visited(g.size(), false);
                std::queue<int> q;
                visited[0] = true;
                q.emplace(0);

                while (q.size()) {
                    int i = q.front();
                    q.pop();
                    auto [cr, cc] = g[i];

                    for (int di = 0; di < 4; ++di) {
                        int nr = cr + dr[di];
                        int nc = cc + dc[di];
                        if (0 <= nr && nr < n && 0 <= nc && nc < n) {
                            auto found = std::find(g.begin(), g.end(), std::make_pair(nr, nc));
                            if (found != g.end()) {
                                int j = found - g.begin();
                                if (!visited[j]) {
                                    visited[j] = true;
                                    q.emplace(j);
                                }
                            }
                        }
                    }
                }

                return std::find(visited.begin(), visited.end(), false) == visited.end();
            };

            if (!areConnected(group[0]) || !areConnected(group[1])) {
                return 0;
            }

            auto rotate = [](Group g) {
                // R = [[cos x, -sin x], [sin x, cos x]]
                // R = [[0, -1], [1, 0]]
                // [[0, -1], [1, 0]] * [[x], [y]] = [[-y], [x]]
                Group result;
                for (auto [r, c] : g) {
                    result.emplace_back(-c, r);
                }
                return result;
            };

            auto normalize = [](Group g) {
                int mr = INT32_MAX, mc = INT32_MAX;
                for (auto [r, c] : g) {
                    mr = std::min(mr, r);
                    mc = std::min(mc, c);
                }
                for (int i = 0; i < g.size(); ++i) {
                    g[i].first -= mr;
                    g[i].second -= mc;
                }
                std::sort(g.begin(), g.end());
                return g;
            };

            auto flip = [&](Group g) {
                for (int i = 0; i < g.size(); ++i) {
                    g[i].second = -g[i].second;
                }
                return g;
            };

            auto areSimilar = [&](const Group& g1, const Group& g2) {
                Group rg1 = g1;
                for (int i = 0; i < 4; ++i) {
                    if (normalize(rg1) == normalize(g2)) {
                        return true;
                    }
                    rg1 = rotate(rg1);
                }
                return false;
            };

            if (!areSimilar(group[0], group[1]) && !areSimilar(flip(group[0]), group[1])) {
                return 0;
            }

            for (auto [r, c] : comp) {
                for (int i = 0; i < 4; ++i) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (0 <= nr && nr < n && 0 <= nc && nc < n) {
                        auto found = std::find(comp.begin(), comp.end(), std::make_pair(nr, nc));
                        if (found != comp.end() && !isConnected(r, c, dr[i], dc[i])) {
                            return 0;
                        }
                    }
                }
            }
        }
        return 1;
    }();

    return 0;
}