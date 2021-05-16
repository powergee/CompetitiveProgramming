#include <iostream>
#include <vector>
#include <algorithm>

struct Cell {
    int r, c;
    bool shark;
};

int main() {
    int n, m;
    std::vector<Cell> cells;
    scanf("%d %d", &n, &m);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            int val;
            scanf("%d", &val);
            cells.push_back({r, c, val == 1});
        }
    }

    int answer = -1;
    for (int i = 0; i < n*m; ++i) {
        if (cells[i].shark) {
            answer = std::max(answer, 0);
            continue;
        }
        int dist = __INT32_MAX__;
        for (int j = 0; j < n*m; ++j) {
            if (cells[j].shark && i != j) {
                dist = std::min(std::max(std::abs(cells[i].r-cells[j].r), std::abs(cells[i].c-cells[j].c)), dist);
            }
        }
        answer = std::max(answer, dist);
    }

    printf("%d", answer);

    return 0;
}