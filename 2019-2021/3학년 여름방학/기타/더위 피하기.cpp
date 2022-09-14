#include <iostream>
#include <algorithm>
#define MOD 1000000007

using Point = std::pair<int, int>;
using Long = long long;

Point init;
int t, n;
Point home;

bool wall[401][401];
Long dp[401][401][201];

int getManDist(Point p1, Point p2) {
    return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

Long countCases(int x, int y, int remain) {
    if (home.first == x && home.second == y) {
        return 1;
    }

    Long& result = dp[x][y][remain];
    if (result != -1) {
        return result;
    }
    if (remain == 0) {
        return result = 0;
    }

    static const int dx[4] = { 0, 0, 1, -1 };
    static const int dy[4] = { 1, -1, 0, 0 };
    result = 0;
    for (int i = 0; i < 4; ++i) {
        int nx = x+dx[i];
        int ny = y+dy[i];
        if (wall[nx][ny]) {
            continue;
        }

        result += countCases(nx, ny, remain-1);
        result %= MOD;
    }

    return result;
}

int main() {
    scanf("%d %d", &init.first, &init.second);
    scanf("%d", &t);
    scanf("%d %d", &home.first, &home.second);
    scanf("%d", &n);

    if (t < getManDist(init, home)) {
        printf("0");
    } else {
        int dx = init.first - 200;
        int dy = init.second - 200;
        init = {200, 200};
        home = {home.first-dx, home.second-dy};

        for (int i = 0; i < n; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            x -= dx;
            y -= dy;
            if (0 <= x && x <= 400 && 0 <= y && y <= 400) {
                wall[x][y] = true;
            }
        }

        std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Long), -1LL);
        std::cout << countCases(200, 200, t);
    }

    return 0;
}