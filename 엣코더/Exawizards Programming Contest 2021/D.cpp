#include <iostream>
#include <algorithm>

typedef long long Long;

int n;
int a[3000], b[3000];
Long dp[3000][3001];

Long countCases(int start, int bound) {
    if (start == n) {
        return 1;
    }
    if (b[start] < bound) {
        return 0;
    }
    if (bound < a[start]) {
        return countCases(start, a[start]);
    }

    Long& result = dp[start][bound];
    if (result != -1) {
        return result;
    }

    result = (countCases(start, bound+1) + countCases(start+1, bound)) % 998244353LL;
    return result;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", a+i);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", b+i);
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1LL);
    printf("%lld", countCases(0, 0));

    return 0;
}