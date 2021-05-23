#include <iostream>
#include <limits>

typedef long long Long;

const Long MAX = std::numeric_limits<int>::max();

int main() {
    int n, m, q;
    Long times[501];
    Long maxTimes[501][501];
    Long dist[501][501];
    Long actualDist[501][501];

    scanf("%d %d %d", &n, &m, &q);

    for (int i = 1; i <= n; ++i) {
        scanf("%lld", times+i);
    }

    for (int i = 1; i < n+1; ++i) {
        for (int j = 1; j < n+1; ++j) {
            dist[i][j] = MAX;
            actualDist[i][j] = MAX;
            maxTimes[i][j] = 0;
        }
        dist[i][i] = 0;
        maxTimes[i][i] = times[i];
    }

    for (int i = 0; i < m; ++i) {
        Long s, e, t;
        scanf("%lld %lld %lld", &s, &e, &t);
        dist[s][e] = std::min(t, dist[s][e]);
        dist[e][s] = std::min(t, dist[e][s]);
        maxTimes[s][e] = std::max(times[s], times[e]);
        maxTimes[e][s] = std::max(times[e], times[s]);
    }

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] + dist[k][j] + std::max(maxTimes[i][k], maxTimes[k][j]) < dist[i][j] + maxTimes[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    maxTimes[i][j] = std::max(maxTimes[i][k], maxTimes[k][j]);
                }
            }
        }
    }

    while (q--) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld\n", (dist[s][t] == MAX ? -1LL : dist[s][t]+maxTimes[s][t]));
    }

    return 0;
}