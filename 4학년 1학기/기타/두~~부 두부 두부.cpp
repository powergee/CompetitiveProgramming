#include <iostream>

typedef long long Long;

int main() {
    Long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    printf("%lld", ((m-1)+(k-3) + 100000*n) % n + 1);

    return 0;
}