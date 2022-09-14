#include <iostream>

typedef long long Long;

Long countOnes(Long x, int startBit = 63) {
    for (int bit = startBit; bit >= 0; --bit) {
        if (x & (1LL<<bit)) {
            return (bit * (1LL<<(bit-1))) + (x - (1LL<<bit) + 1) + countOnes(x - (1LL<<bit), bit-1);
        }
    }
    return 0;
}

int main() {
    Long a, b;
    scanf("%lld %lld", &a, &b);
    printf("%lld", countOnes(b) - countOnes(a-1));

    return 0;
}