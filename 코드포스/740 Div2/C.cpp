#include <iostream>
#include <algorithm>

typedef long long Long;

std::pair<Long, int> caves[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            int m;
            scanf("%d", &m);
            Long beforePower = 0;
            for (int j = 0; j < m; ++j) {
                Long mob;
                scanf("%lld", &mob);
                beforePower = std::max(beforePower, mob-j+1);
            }
            caves[i] = { beforePower, m };
        }

        std::sort(caves, caves+n);
        Long initPower = 0, earned = 0;
        for (int i = 0; i < n; ++i) {
            initPower = std::max(initPower, caves[i].first-earned);
            earned += caves[i].second;
        }

        printf("%lld\n", initPower);
    }

    return 0;
}