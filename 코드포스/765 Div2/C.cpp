#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    int n, l, k;
    scanf("%d %d %d", &n, &l, &k);

    std::vector<Long> coord(n), limit(n);
    std::for_each(coord.begin(), coord.end(), [](Long& v) { scanf("%lld", &v); });
    std::for_each(limit.begin(), limit.end(), [](Long& v) { scanf("%lld", &v); });
    coord.push_back(l);

    std::vector<std::vector<Long>> dp(n+1, std::vector<Long>(k+1, INT64_MAX));
    for (int i = 0; i <= k; ++i) {
        dp[n][i] = 0;
    }

    for (int start = n-1; start >= 0; --start) {
        for (int used = 0; used <= k; ++used) {
            for (int end = start+1; end <= n && (end-start-1) <= (k-used); ++end) {
                dp[start][used] = std::min(dp[start][used], limit[start] * (coord[end]-coord[start]) + dp[end][used+(end-start-1)]);
            }
        }
    }

    printf("%lld", dp[0][0]);

    return 0;
}