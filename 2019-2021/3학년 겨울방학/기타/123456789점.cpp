#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, s;
        scanf("%lld %lld", &n, &s);

        // x+y+z+w <= n
        // floor(10^9 * (2x+2y+z) / (2N)) + x = s
        auto calcScore = [&](Long good) -> Long {
            return (1000000000LL*good) / (2*n);
        };

        Long left = 0, right = 2*n;
        while (left+1 < right) {
            Long mid = (left+right) / 2;
            if (s < calcScore(mid)) {
                right = mid-1;
            } else {
                left = mid;
            }
        }

        Long good;
        if (s < calcScore(right)) {
            good = left;
        } else {
            good = right;
        }

        Long need = s-calcScore(good);
        Long maxPerfect = good / 2;
        if (need < 0 || maxPerfect < need) {
            printf("-1\n");
        } else {
            printf("%lld %lld\n", good, need);
        }
    }

    return 0;
}