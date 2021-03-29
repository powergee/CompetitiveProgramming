#include <iostream>

long long getGCD(long long u, long long v) {
    long long t;

    while (v)
    {
        t = u % v;
        u = v;
        v = t;
    }

    return u;
}

long long sumDigit(long long u) {
    long long sum = 0;
    while (u) {
        sum += u % 10;
        u /= 10;
    }
    return sum;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n;
        scanf("%lld", &n);

        for (;; ++n) {
            if (getGCD(n, sumDigit(n)) > 1) {
                printf("%lld\n", n);
                break;
            }
        }
    }
}