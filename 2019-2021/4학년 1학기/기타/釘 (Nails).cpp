#include <iostream>
#include <vector>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> map(n+2);
    for (int i = 0; i < n+2; ++i) {
        map[i].resize(i+3, 0);
    }

    for (int i = 0; i < m; ++i) {
        int r, c, l;
        scanf("%d %d %d", &r, &c, &l);
        --r, --c;
        map[r][c]++;
        map[r][c+1]--;
        map[r+l+1][c]--;
        map[r+l+1][c+l+2]++;
        map[r+l+2][c+1]++;
        map[r+l+2][c+l+2]--;
    }

    for (int r = 0; r < map.size(); ++r) {
        for (int c = 1; c < map[r].size(); ++c) {
            map[r][c] += map[r][c-1];
        }
    }
    for (int r = 1; r < map.size(); ++r) {
        for (int c = 1; c < map[r].size(); ++c) {
            map[r][c] += map[r-1][c-1];
        }
    }
    for (int c = 0; c < map.back().size(); ++c) {
        for (int r = std::max(1, c-1); r < map.size(); ++r) {
            map[r][c] += map[r-1][c];
        }
    }

    int count = 0;
    for (auto& row : map) {
        for (auto& v : row) {
            count += (v > 0 ? 1 : 0);
        }
    }
    printf("%d", count);

    return 0;
}