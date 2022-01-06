#include <iostream>
#include <numeric>
#include <cmath>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long a, b;
        scanf("%lld %lld", &a, &b);
        Long diff = std::abs(a-b);

        if (diff == 0) {
            printf("0 0\n");
        } else if (std::gcd(a, b) == diff) {
            printf("%lld 0\n", diff);
        } else {
            Long as1 = (a / diff + 1) * diff;
            Long bs1 = (b / diff + 1) * diff;
            Long dist1 = std::abs(as1-a);

            Long as2 = (a / diff) * diff;
            Long bs2 = (b / diff) * diff;
            Long dist2 = std::abs(as2-a);

            if (dist1 < dist2) {
                printf("%lld %lld\n", std::gcd(as1, bs1), dist1);
            } else {
                printf("%lld %lld\n", std::gcd(as2, bs2), dist2);
            }
        }
    }

    return 0;
}