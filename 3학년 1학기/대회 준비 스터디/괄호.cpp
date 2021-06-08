#include <iostream>
#include <algorithm>
#define MOD 1000000007LL

typedef long long Long;

Long dp[5001][5001];

Long countCases(int toFill, int before) {
    Long& result = dp[toFill][before];
    if (result != -1LL) {
        return result;
    }

    if (toFill == 0) {
        if (before == 0) {
            return result = 1;
        } else {
            return result = 0;
        }
    }

    result = 0;
    if (before >= 1) {
        result += countCases(toFill-1, before-1);
        result %= MOD;
    }
    result += countCases(toFill-1, before+1);
    result %= MOD;

    return result;
}

int main() {
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1LL);

    int T;
    scanf("%d", &T);

    while (T--) {
        int l;
        scanf("%d", &l);
        printf("%lld\n", countCases(l, 0));
    }

    return 0;
}