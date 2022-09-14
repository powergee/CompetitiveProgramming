#include <iostream>
#include <algorithm>

typedef long double Long;

int m, k;
int count[50];
Long combDP[51][51];
Long dp[50][2501];

Long calcComb(int n, int m) {
    if (n < m) {
        return 0;
    } else if (n == 0 || m == 0) {
        return 1;
    } else if (combDP[n][m] != -1) {
        return combDP[n][m];
    } else {
        return combDP[n][m] = calcComb(n-1, m-1) + calcComb(n-1, m);
    }
}

Long countAllComb(int start, int remain) {
    if (remain == 0) {
        return 1;
    }
    if (start == m) {
        return 0;
    }

    Long& result = dp[start][remain];
    if (result != -1) {
        return result;
    }

    result = 0;
    for (int i = 0; i <= std::min(remain, count[start]); ++i) {
        result += calcComb(count[start], i) * countAllComb(start+1, remain-i);
    }
    return result;
}

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d", count+i);
    }
    scanf("%d", &k);

    std::fill(&combDP[0][0], &combDP[0][0] + sizeof(combDP) / sizeof(Long), -1LL);
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1LL);

    Long sameComb = 0;
    for (int i = 0; i < m; ++i) {
        sameComb += calcComb(count[i], k);
    }

    printf("%.14Lf", sameComb / countAllComb(0, k));

    return 0;
}