#include <iostream>
#include <algorithm>
#include <set>
#define MOD 998244353

using Long = long long;

Long sumCases(int day);
Long countCases(int prev, int day);

Long mod(Long val, Long m) {
    if (val < 0) {
        return mod(val + m, m);
    }
    return val % m;
}

int n, m, k;
std::set<int> unusable[5001];
Long dp[5001][5001];
Long sumDp[5001];

Long sumCases(int day) {
    Long& result = sumDp[day];
    if (result != -1) {
        return result;
    }

    result = 0;
    for (int next = 1; next <= n; ++next) {
        result += countCases(next, day);
        result = mod(result, MOD);
    }

    return result;
}

Long countCases(int prev, int day) {
    if (day == k) {
        return (prev == 1 || unusable[prev].find(1) != unusable[prev].end() ? 0 : 1);
    }

    Long& result = dp[prev][day];
    if (result != -1) {
        return result;
    }

    result = sumCases(day+1) - countCases(prev, day+1);
    result = mod(result, MOD);
    for (int next : unusable[prev]) {
        result -= countCases(next, day+1);
        result = mod(result, MOD);
    }

    return result;
}

int main() {
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Long), -1LL);
    std::fill(&sumDp[0], &sumDp[0] + sizeof(sumDp) / sizeof(Long), -1LL);
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        unusable[u].insert(v);
        unusable[v].insert(u);
    }

    printf("%lld", countCases(1, 1));
    return 0;
}