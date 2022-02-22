#include <iostream>

typedef long long Long;

Long getLeastMask(Long n) {
    Long result = 1;
    while (result < n) {
        result <<= 1;
        result += 1;
    }
    return result;
}

int main() {
    Long n;
    scanf("%lld", &n);

    Long mask = getLeastMask(n);
    if (mask == n) {
        printf("1\n%lld", n);
    } else {
        printf("2\n%lld %lld", mask-n, n);
    }

    return 0;
}