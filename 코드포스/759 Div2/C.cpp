#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

typedef long long Long;

Long getMinDist(std::vector<Long>& points, int k) {
    int n = points.size();
    std::function<Long(int)> getSubDist;
    getSubDist = [&](int end) -> Long {
        if (end < 0) {
            return 0;
        }
        return getSubDist(end-k) + points[end]*2;
    };

    Long minDist = INT64_MAX;
    for (int i = 0; i < k; ++i) {
        int p = n-1-i;
        Long dist = getSubDist(p) + (p < n-1 ? points[n-1]*2 : 0);
        minDist = std::min(dist, minDist);
    }
    return minDist;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<Long> pos, neg;
        pos.push_back(0);
        neg.push_back(0);
        for (int i = 0; i < n; ++i) {
            Long val;
            scanf("%lld", &val);
            if (val > 0) {
                pos.push_back(val);
            } else {
                neg.push_back(-val);
            }
        }
        std::sort(pos.begin(), pos.end());
        std::sort(neg.begin(), neg.end());

        Long left = getMinDist(neg, k);
        Long right = getMinDist(pos, k);
        printf("%lld\n", left + right - std::max(pos.back(), neg.back()));
    }

    return 0;
}
