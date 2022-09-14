#include <iostream>

using Long = long long;
Long dp[21][21][21];

Long countCases(int poles, int left, int right) {
    if (poles == 1) {
        return (left == 1 && right == 1 ? 1 : 0);
    }
    if (left <= 0 || right <= 0) {
        return 0;
    }

    Long& result = dp[poles][left][right];
    if (result != -1) {
        return result;
    }

    result = 0;
    result += countCases(poles-1, left-1, right);
    result += countCases(poles-1, left, right-1);
    result += (poles-2) * countCases(poles-1, left, right);
    return result;
}

int main() {
    std::fill(&dp[0][0][0], &dp[0][0][0]+sizeof(dp)/sizeof(Long), -1LL);
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, l, r;
        scanf("%d %d %d", &n, &l, &r);
        printf("%lld\n", countCases(n, l, r));
    }

    return 0;
}