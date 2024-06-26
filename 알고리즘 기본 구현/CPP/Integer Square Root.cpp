#include <algorithm>

typedef long long Long;

// Heron's Method
Long getIntSqrt(Long n) {
    if (n <= 1) {
        return n;
    }

    Long x0 = n;
    Long x1 = std::min(1LL<<((64-__builtin_clzll(n))/2+1), n/2);
    while (x1 < x0) {
        x0 = x1;
        x1 = (x0 + n/x0) / 2;
    }
    return x0;
}