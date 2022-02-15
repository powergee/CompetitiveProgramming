#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> map(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &map[i][j]);
        }
    }

    auto isValid = [&](int r, int c) -> bool {
        return 0 <= r && r < n-1 && 0 <= c && c < m-1;
    };

    auto getRepColor = [&](std::pair<int, int> p) -> int {
        int color = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (map[p.first+i][p.second+j] != 0) {
                    if (color != 0 && color != map[p.first+i][p.second+j]) {
                        return -1;
                    } else {
                        color = map[p.first+i][p.second+j];
                    }
                }
            }
        }
        return color;
    };

    auto clearPosition = [&](std::pair<int, int> p) {
        map[p.first][p.second] = map[p.first][p.second+1] = map[p.first+1][p.second] = map[p.first+1][p.second+1] = 0;
    };

    std::stack<std::tuple<int, int, int>> jobs;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    std::function<void(std::pair<int, int>)> DFS = [&](std::pair<int, int> curr) {
        int color = getRepColor(curr);
        if (color <= 0) {
            return;
        }
        visited[curr.first][curr.second] = true;
        jobs.emplace(curr.first+1, curr.second+1, getRepColor(curr));
        clearPosition(curr);

        const int dr[4] { 0, 0, 1, -1 };
        const int dc[4] { 1, -1, 0, 0 };
        for (int i = 0; i < 4; ++i) {
            int nr = dr[i]+curr.first;
            int nc = dc[i]+curr.second;
            if (isValid(nr, nc) && getRepColor({nr, nc}) > 0 && !visited[nr][nc]) {
                DFS({nr, nc});
            }
        }
    };

    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < m-1; ++j) {
            if (!visited[i][j] && getRepColor({i, j}) > 0) {
                DFS({i, j});
            }
        }
    }

    bool isPossible = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] != 0) {
                isPossible = false;
            }
        }
    }

    if (isPossible) {
        printf("%d\n", int(jobs.size()));
        while (!jobs.empty()) {
            auto [i, j, c] = jobs.top();
            jobs.pop();
            printf("%d %d %d\n", i, j, c);
        }
    } else {
        printf("-1\n");
    }

    return 0;
}