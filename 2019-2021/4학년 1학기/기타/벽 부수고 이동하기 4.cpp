#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

class DisjointSet {
private:
    std::vector<int> parent;
public:
    DisjointSet(int count) {
        parent.resize(count);
        for (int i = 0; i < count; ++i) {
            parent[i] = i;
        }
    }

    int findParent(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = findParent(parent[x]);
    }

    void unionNodes(int x, int y) {
        int xPar = findParent(x);
        int yPar = findParent(y);

        parent[xPar] = yPar;
    }
};

int main() {
    static const int dr[] { 0, 0, 1, -1 };
    static const int dc[] { 1, -1, 0, 0 };

    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    auto isValid = [&](int r, int c) { return 0 <= r && r < n && 0 <= c && c < m; };
    auto toIndex = [&](int r, int c) { return r*m + c; };

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    DisjointSet dsu(n*m);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            for (int i = 0; i < 4; ++i) {
                int nr = r+dr[i], nc = c+dc[i];
                if (map[r][c] == '0' && isValid(nr, nc) && map[nr][nc] == '0') {
                    dsu.unionNodes(toIndex(r, c), toIndex(nr, nc));
                }
            }
        }
    }

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    std::vector<std::vector<int>> size(n, std::vector<int>(m));
    auto getSize = [&](int sr, int sc) -> int {
        std::queue<std::pair<int, int>> q;
        q.emplace(sr, sc);
        visited[sr][sc] = true;
        int result = 1;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nr = r+dr[i], nc = c+dc[i];
                if (isValid(nr, nc) && map[nr][nc] == '0' && !visited[nr][nc]) {
                    q.emplace(nr, nc);
                    visited[nr][nc] = true;
                    ++result;
                }
            }
        }

        return result;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!visited[i][j] && map[i][j] == '0') {
                int rep = dsu.findParent(toIndex(i, j));
                size[rep/m][rep%m] = getSize(i, j);
            }
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (map[r][c] == '0') {
                std::cout << "0";
            } else {
                std::set<int> neigh;
                for (int i = 0; i < 4; ++i) {
                    int nr = r+dr[i], nc = c+dc[i];
                    if (isValid(nr, nc) && map[nr][nc] == '0') {
                        neigh.insert(dsu.findParent(toIndex(nr, nc)));
                    }
                }
                int result = 1;
                for (int nIdx : neigh) {
                    int r = nIdx/m, c = nIdx%m;
                    result += size[r][c];
                }
                std::cout << result % 10;
            }
        }
        std::cout << "\n";
    }

    return 0;
}