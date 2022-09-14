#include <iostream>
#include <algorithm>
#include <vector>
#define MOD 1000000009LL

typedef long long Long;

int main() {
    Long n, y;
    scanf("%lld %lld", &n, &y);
    Long originY = y;

    std::vector<Long> primes;
    for (Long div = 2; div*div <= originY; ++div) {
        int count = 0;
        while (y % div == 0) {
            y /= div;
            ++count;
        }
        if (count) {
            primes.push_back(div);
        }
    }
    if (y > 1) {
        primes.push_back(y);
    }
    y = originY;

    std::vector<std::pair<Long, int>> exclude;
    exclude.reserve(1<<primes.size());
    for (int mask = 0; mask < (1<<primes.size()); ++mask) {
        Long mult = 1;
        for (int i = 0; i < primes.size(); ++i) {
            if (mask&(1<<i)) {
                mult *= primes[i];
            }
        }
        exclude.emplace_back(mult, (__builtin_popcount(mask) % 2 == 0 ? 1 : -1));
    }

    std::vector<Long> subPow(exclude.size());
    for (int i = 0; i < exclude.size(); ++i) {
        subPow[i] = y/exclude[i].first;
    }
    std::vector<Long> lPow(n+1);
    lPow[n] = 1;
    for (int i = n-1; i >= 1; --i) {
        lPow[i] = (lPow[i+1] * y) % MOD;
    }

    Long answer = 0;
    for (int l = 1; l <= n; ++l) {
        Long sub = 0;
        for (int i = 0; i < exclude.size(); ++i) {
            auto [mult, coeff] = exclude[i];
            sub += coeff * subPow[i] + MOD;
            sub %= MOD;
            subPow[i] = (subPow[i] * (y/mult)) % MOD;
        }
        answer += (((sub * (n-l+1)) % MOD) * lPow[l]) % MOD;
        answer %= MOD;
    }
    printf("%lld\n", answer);

    return 0;
}