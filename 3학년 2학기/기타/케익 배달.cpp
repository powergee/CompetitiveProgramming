#include <iostream>
#include <algorithm>

typedef long long Long;

std::pair<int, int> getNeighbor(std::pair<int, int> origin, int dir) {
    const static int dr[5] { 0, 0, 1, -1, 0 };
    const static int dc[5] { 1, -1, 0, 0, 0 };
    return { origin.first+dr[dir], origin.second+dc[dir] };
}

int main() {
    int n;
    scanf("%d", &n);

    std::pair<int, int> origin;
    scanf("%d %d", &origin.first, &origin.second);

    std::pair<int, int> points[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i].first, &points[i].second);
    }

    Long dp[n][5];
    for (int d = 0; d < 5; ++d) {
        auto p = getNeighbor(points[0], d);
        dp[0][d] = std::abs(p.first-origin.first) + std::abs(p.second-origin.second);
    }
    for (int i = 1; i < n; ++i) {
        for (int d1 = 0; d1 < 5; ++d1) {
            dp[i][d1] = INT64_MAX;
            for (int d2 = 0; d2 < 5; ++d2) {
                auto p1 = getNeighbor(points[i], d1);
                auto p2 = getNeighbor(points[i-1], d2);
                dp[i][d1] = std::min(dp[i][d1], dp[i-1][d2] + (std::abs(p1.first-p2.first) + std::abs(p1.second-p2.second)));
            }
        }
    }

    printf("%lld", *std::min_element(dp[n-1], dp[n-1]+5));

    return 0;
}