#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    std::vector<std::pair<int, int>> cells;
    cells.reserve(q+2);
    cells.emplace_back(1, 1);
    cells.emplace_back(n, n);
    for (int i = 0; i < q; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        cells.emplace_back(r, c);
    }

    std::vector<std::vector<int>> dp(q+2, std::vector<int>(q+2, -1));
    std::vector<std::vector<std::pair<int, int>>> next(q+2, std::vector<std::pair<int, int>>(q+2, {-1, -1}));
    std::function<int(int, int)> getMinSum = [&](int p1, int p2) -> int {
        if (dp[p1][p2] != -1) {
            return dp[p1][p2];
        }
        
        int job = std::max(p1, p2) + 1;
        if (job >= q+2) {
            return dp[p1][p2] = 0;
        }

        dp[p1][p2] = getMinSum(job, p2)
            + std::abs(cells[p1].first-cells[job].first)
            + std::abs(cells[p1].second-cells[job].second);
        next[p1][p2] = { job, p2 };

        int alt = getMinSum(p1, job)
            + std::abs(cells[p2].first-cells[job].first)
            + std::abs(cells[p2].second-cells[job].second);

        if (alt < dp[p1][p2]) {
            dp[p1][p2] = alt;
            next[p1][p2] = { p1, job };
        }

        return dp[p1][p2];
    };

    int sum = getMinSum(0, 1);
    printf("%d\n", sum);

    std::pair<int, int> state = { 0, 1 };
    while (state.first != -1) {
        auto nxt = next[state.first][state.second];
        if (nxt.first != -1) {
            if (state.first != nxt.first) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 2);
            }
        }
        state = nxt;
    }

    return 0;
}