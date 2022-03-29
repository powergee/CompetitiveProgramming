#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

typedef long long Long;

struct Unit {
    Long c, d, h;
};

struct Monster {
    Long d, h;
    int index;
};

int main() {
    Long n, maxC;
    scanf("%lld %lld", &n, &maxC);

    std::vector<Long> maxKillable(maxC+1, 0);
    for (int i = 0; i < n; ++i) {
        Long c, d, h;
        scanf("%lld %lld %lld", &c, &d, &h);
        if (c <= maxC) {
            maxKillable[c] = std::max(maxKillable[c], d*h);
        }
    }

    for (Long i = 1; i <= maxC; ++i) {
        maxKillable[i] = std::max(maxKillable[i], maxKillable[i-1]);
        for (Long j = 2*i; j <= maxC; j += i) {
            maxKillable[j] = std::max(maxKillable[j], j/i*maxKillable[i]);
        }
    }

    Long m;
    scanf("%lld", &m);

    std::vector<Monster> monsters(m);
    std::vector<Long> answer(m, -1);
    for (int i = 0; i < m; ++i) {
        Long d, h;
        scanf("%lld %lld", &d, &h);
        monsters[i] = {d, h, i};
    }

    std::sort(monsters.begin(), monsters.end(), [](Monster m1, Monster m2) { return m1.d*m1.h < m2.d*m2.h; });
    int mIdx = 0;
    for (int i = 1; i <= maxC; ++i) {
        while (mIdx < m) {
            auto monst = monsters[mIdx];
            if (monst.d * monst.h < maxKillable[i]) {
                answer[monst.index] = i;
                mIdx++;
            } else {
                break;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        printf("%lld ", answer[i]);
    }

    return 0;
}