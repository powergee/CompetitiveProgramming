#include <cstdio>
#include <iostream>
#include <numeric>
typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);

        for (Long p = 2; p < n-2; ++p) {
            Long q = n-1 - p;
            if (std::gcd(p, q) == 1) {
                printf("%lld %lld %lld\n", p, q, 1LL);
                break;
            }
        }
    }
}
