#include <iostream>
#include <vector>
#include <string>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    int sr, sc;
    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 'I') {
                sr = i;
                sc = j;
            }
        }
    }

    int count = 0;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::queue<std::pair<int, int>> q;
    visited[sr][sc] = true;
    q.push({sr, sc});
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (map[r][c] == 'P') {
            count += 1;
        }
        
        static const std::vector<std::pair<int, int>> DELTA = {
            { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
        };
        for (auto [dr, dc] : DELTA) {
            int nr = dr+ r;
            int nc  = dc + c;
            if (0 <= nr && nr < n && 0 <= nc && nc < m && !visited[nr][nc] && map[nr][nc] != 'X') {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }

    if (count == 0) {
        std::cout << "TT\n";
    } else {
        std::cout << count << "\n";
    }

    return 0;
}