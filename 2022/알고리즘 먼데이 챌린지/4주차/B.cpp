#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> map(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> map[i][j];
        }
    }

    auto isFinished = [&]() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (map[i][j] > 0) {
                    return false;
                }
            }
        }
        return true;
    };

    auto countNeigh = [&](int r, int c) {
        const static int dx[] = { 0, 0, 1, -1 };
        const static int dy[] = { 1, -1, 0, 0 };
        int count = 0;
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (0 <= nr && nr < n && 0 <= nc && nc < n && map[nr][nc] == 0) {
                ++count;
            }
        }
        return count;
    };

    int day = 0;
    while (!isFinished()) {
        ++day;
        auto next = map;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                next[i][j] = std::max(0, map[i][j] - countNeigh(i, j));
            }
        }
        map = next;
    }

    std::cout << day;

    return 0;
}