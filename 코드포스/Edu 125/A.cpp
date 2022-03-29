#include <iostream>
#include <vector>

int dp[51][51];

// Heron's Method
int getIntSqrt(int n) {
    if (n <= 1) {
        return n;
    }

    int x0 = n;
    int x1 = std::min(1<<((32-__builtin_clz(n))/2+1), n/2);
    while (x1 < x0) {
        x0 = x1;
        x1 = (x0 + n/x0) / 2;
    }
    return x0;
}

bool isPerfectSquare(int n) {
    int sqrt = getIntSqrt(n);
    return sqrt * sqrt == n;
}

int getMinDist(int x, int y) {
    if (x == 0 && y == 0) {
        return 0;
    }

    if (dp[x][y] != 0) {
        return dp[x][y];
    }

    dp[x][y] = INT32_MAX;
    for (int i = 0; i <= x; ++i) {
        for (int j = 0; j <= y; ++j) {
            if (i == x && j == y) {
                continue;
            }
            int distSq = (x-i)*(x-i) + (y-j)*(y-j);
            if (isPerfectSquare(distSq)) {
                dp[x][y] = std::min(dp[x][y], getMinDist(i, j) + 1);
            }
        }
    }
    return dp[x][y];
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", getMinDist(x, y));
    }

    return 0;
}