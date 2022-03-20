#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <set>

typedef long long Long;

Long dp[2001][2001][2];

int main() {
    int n, m, k, s, t, x;
    scanf("%d %d %d %d %d %d", &n, &m, &k, &s, &t, &x);

    std::vector<std::set<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].insert(v);
        graph[v].insert(u);
    }

    for (int v = 1; v <= n; ++v) {
        for (int r = 0; r <= k; ++r) {
            for (int isEven = 0; isEven < 2; ++isEven) {
                dp[v][r][isEven] = 0;
                dp[v][r][isEven] = 0;
            }
        }
    }
    dp[t][0][1] = 1;

    for (int remain = 1; remain <= k; ++remain) {
        for (int curr = 1; curr <= n; ++curr) {
            for (int isEven = 0; isEven < 2; ++isEven) {
                for (int next : graph[curr]) {
                    dp[curr][remain][isEven] += dp[next][remain-1][next == x ? (isEven ? 0 : 1) : isEven];
                    dp[curr][remain][isEven] %= 998244353LL;
                }
            }
        }
    }
    printf("%lld", dp[s][k][1]);

    return 0;
}