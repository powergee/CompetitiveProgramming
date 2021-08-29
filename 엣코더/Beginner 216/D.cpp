#include <iostream>
#include <vector>
#include <algorithm>
#define UNDEFINED -1
#define JUDGING -2

std::vector<int> cylinders[200000];
std::vector<std::pair<int, int>> positions[200001];
int dp[200001];

bool isAbleToPop(int color) {
    if (dp[color] == JUDGING) {
        return false;
    }
    if (dp[color] != UNDEFINED) {
        return dp[color] == 1;
    }

    dp[color] = JUDGING;
    bool areTop = true;
    for (auto p : positions[color]) {
        if (p.second != 0) {
            areTop = false;
        }
    }
    if (areTop) {
        return dp[color] = 1;
    }

    for (auto p : positions[color]) {
        if (p.second > 0 && !isAbleToPop(cylinders[p.first][p.second-1])) {
            return dp[color] = 0;
        }
    }

    return dp[color] = 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int k;
        scanf("%d", &k);
        cylinders[i].resize(k);
        for (int j = 0; j < k; ++j) {
            scanf("%d", &cylinders[i][j]);
            positions[cylinders[i][j]].emplace_back(i, j);
        }
    }

    std::fill(dp+1, dp+n+1, UNDEFINED);
    bool yes = true;
    for (int c = 1; c <= n; ++c) {
        if (!isAbleToPop(c)) {
            yes = false;
        }
    }

    printf(yes ? "Yes" : "No");

    return 0;
}