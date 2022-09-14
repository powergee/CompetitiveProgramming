#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using Map = std::vector<std::string>;

void applyXOR(Map& map, int r, int c) {
    const static int dr[5] { 0, -1, 0, 1, 0 };
    const static int dc[5] { 0, 0, 1, 0, -1 };
    for (int i = 0; i < 5; ++i) {
        int nr = r+dr[i];
        int nc = c+dc[i];
        if (0 <= nr && nr < 10 && 0 <= nc && nc < 10) {
            map[nr][nc] = (map[nr][nc] == '#' ? 'O' : '#');
        }
    }
}

int main() {
    Map origin(10);
    for (int i = 0; i < 10; ++i) {
        std::cin >> origin[i];
    }

    std::vector<int> cands;
    for (int mask = 0; mask < (1<<10); ++mask) {
        int count = 0;
        Map map = origin;
        for (int i = 0; i < 10; ++i) {
            if (mask&(1<<i)) {
                applyXOR(map, 0, i);
                ++count;
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (map[i][j] == 'O') {
                    applyXOR(map, i+1, j);
                    ++count;
                }
            }
        }

        bool succeed = true;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (map[i][j] == 'O') {
                    succeed = false;
                }
            }
        }

        if (succeed) {
            cands.push_back(count);
        }
    }

    std::cout << (cands.empty() ? -1 : *std::min_element(cands.begin(), cands.end()));

    return 0;
}