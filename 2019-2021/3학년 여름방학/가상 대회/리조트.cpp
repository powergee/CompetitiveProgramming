#include <iostream>
#include <algorithm>

int n, m;
bool isFree[101];
int dp[101][100];

int getMinCost(int start, int coupons) {
    if (n < start) {
        return 0;
    }
    if (dp[start][coupons] != -1) {
        return dp[start][coupons];
    }

    if (isFree[start]) {
        int cases[] = {
            10000 + getMinCost(start+1, coupons),
            25000 + getMinCost(start+3, coupons+1),
            37000 + getMinCost(start+5, coupons+2),
            (coupons >= 3 ? getMinCost(start+1, coupons-3) : __INT32_MAX__)
        };
        return dp[start][coupons] = *std::min_element(cases, cases+4);
    } else {
        return dp[start][coupons] = getMinCost(start+1, coupons);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    std::fill(isFree+1, isFree+n+1, true);

    for (int i = 0; i < m; ++i) {
        int day;
        scanf("%d", &day);
        isFree[day] = false;
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    printf("%d", getMinCost(1, 0));

    return 0;
}