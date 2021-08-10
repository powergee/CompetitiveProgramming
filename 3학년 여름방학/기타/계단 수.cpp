#include <iostream>
#include <algorithm>
#define MOD 1000000000

typedef long long Long;

Long dp[101][10][1<<10];

Long countCases(int count, int prev, int appeared) {
    Long& result = dp[count][prev][appeared];
    if (result != -1) {
        return result;
    }

    if (count == 0) {
        return result = ((appeared == ((1<<10)-1)) ? 1 : 0);
    }
    
    result = 0;
    if (prev < 9) {
        result += countCases(count-1, prev+1, appeared|(1<<(prev+1)));
    }
    if (prev > 0) {
        result += countCases(count-1, prev-1, appeared|(1<<(prev-1)));
    }
    result %= MOD;

    return result;
}

Long countCases(int count) {
    Long result = 0;
    for (int i = 1; i <= 9; ++i) {
        result += countCases(count-1, i, (1<<i));
        result %= MOD;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Long), -1LL);
    printf("%lld", countCases(n));

    return 0;
}