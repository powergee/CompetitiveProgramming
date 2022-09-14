#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    Long n;
    std::cin >> n;

    std::vector<Long> primes;
    Long tempN = n;
    for (Long p = 2; p*p <= n; ++p) {
        int count = 0;
        while (tempN % p == 0) {
            tempN /= p;
            ++count;
        }
        if (count) {
            primes.push_back(p);
        }
    }
    if (tempN >= 2) {
        primes.push_back(tempN);
    }

    Long count = n;
    for (int mask = 1; mask < (1<<primes.size()); ++mask) {
        Long mult = 1;
        for (int i = 0; i < primes.size(); ++i) {
            if (mask & (1<<i)) {
                mult *= primes[i];
            }
        }
        count += (n/mult) * ((__builtin_popcount(mask) % 2) ? -1 : 1);
    }
    std::cout << count;

    return 0;
}