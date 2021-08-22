#include <iostream>
#include <algorithm>
#define MOD 998244353

typedef long long Long;

int n;
char str[1001];
Long dp[1000][1<<10][11];

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        Long pow = getModPow(val, exp/2);
        return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
    }
}

Long countCases(int start, int selected, int prev) {
    if (start == n) {
        return selected == 0 ? 0 : 1;
    }

    Long& result = dp[start][selected][prev];
    if (result != -1) {
        return result;
    }

    int end;
    for (end = start; end+1 < n && str[end+1] == str[start]; ++end);

    result = countCases(end+1, selected, prev);
    if ((selected & (1<<(str[start]-'A'))) == 0 || prev == str[start]-'A') {
        result += (getModPow(2, end-start+1)-1) * countCases(end+1, (selected | (1<<(str[start]-'A'))), str[start]-'A');
        result %= MOD;
    }

    return result;
}

int main() {
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Long), -1LL);
    scanf("%d", &n);
    scanf("%s", str);
    printf("%lld", countCases(0, 0, 10));

    return 0;
}