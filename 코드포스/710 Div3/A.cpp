#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n, m, x;
        scanf("%lld %lld %lld", &n, &m, &x);
        --x;

        long long r = x % n;
        long long c = (x-r) / n;

        printf("%lld\n", m*r + c + 1);
    }
}