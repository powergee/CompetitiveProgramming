#include <iostream>
#include <algorithm>
#define int long long

int n, m;
std::pair<int, int> anton;

int getDist(std::pair<int, int> p1, std::pair<int, int> p2) {
    return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}

int getTravelDist(std::pair<int, int> y1, std::pair<int, int> y2) {
    int d1 = getDist(anton, y1) + getDist(y1, y2) + getDist(y2, anton);
    int d2 = getDist(anton, y2) + getDist(y2, y1) + getDist(y1, anton);
    return std::min(d1, d2);
}

int32_t main() {
    int T;
    scanf("%lld", &T);

    while (T--) {
        scanf("%lld %lld %lld %lld", &n, &m, &anton.first, &anton.second);

        std::pair<int, int> ul(1, 1);
        std::pair<int, int> ur(1, m);
        std::pair<int, int> ll(n, 1);
        std::pair<int, int> lr(n, m);
        std::pair<int, int> pos[] = {
            ul, ur, ll, lr
        };

        std::pair<int, int> ans[2];
        int maxDist = -1;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int dist = getTravelDist(pos[i], pos[j]);
                if (maxDist < dist) {
                    maxDist = dist;
                    ans[0] = pos[i];
                    ans[1] = pos[j];
                }
            }
        }

        printf("%lld %lld %lld %lld\n", ans[0].first, ans[0].second, ans[1].first, ans[1].second);
    }

    return 0;
}