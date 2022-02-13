#include <iostream>
#include <map>
#define MOD 998244353

typedef long long Long;

std::map<Long, Long> cache;

Long getMaxMult(Long n) {
    if (cache.find(n) != cache.end()) {
        return cache[n];
    }
    if (n <= 3) {
        return cache[n] = n;
    }

    if (n % 2 == 0) {
        Long sub = getMaxMult(n/2) % MOD;
        return cache[n] = (sub * sub) % MOD;
    } else {
        Long s1 = getMaxMult(n/2) % MOD;
        Long s2 = getMaxMult(n/2+1) % MOD;
        return cache[n] = (s1 * s2) % MOD;
    }
}

int main() {
    Long n;
    std::cin >> n;
    std::cout << getMaxMult(n);
    return 0;
}