#include <iostream>
#include <algorithm>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long p, q, a, b, c, d;
        scanf("%lld %lld %lld %lld %lld %lld", &p, &q, &a, &b, &c, &d);

        Long bit = p;
        Long coin = q/c*d;
        Long answer = std::min(bit, coin);
        bit -= answer;
        coin -= answer;

        if (bit) {
            answer += bit / (a+b) * b;
            answer += std::max((bit % (a+b)) - a, 0LL);
        } else if (coin) {
            answer += coin / (a+b) * a;
            answer += std::max((coin % (a+b)) - b, 0LL);
        }

        printf("%lld\n", answer);
    }

    return 0;
}