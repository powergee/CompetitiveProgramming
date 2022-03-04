#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, s;
        scanf("%lld %lld", &n, &s);
        printf("%lld\n", s / (n*n));
    }

    return 0;
}