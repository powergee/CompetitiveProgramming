#include <iostream>
#include <vector>
#include <algorithm>

// Faster
std::vector<int> getPrimes(int last) {
    if (last < 2) {
        return std::vector<int>();
    }

    std::vector<bool> isPrime(last + 1, true);
    isPrime[0] = isPrime[1] = false;
    std::vector<int> primes;

    for (int div = 2; div*div <= last; ++div) {
        if (isPrime[div]) {
            for (int i = div*div; i <= last; i += div) {
                isPrime[i] = false;
            }
        }
    }

    for (int i = 2; i < last + 1; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    auto primes = getPrimes(10000);
    std::vector<int> mult;
    for (int i = 0; i < int(primes.size())-1; ++i) {
        mult.push_back(primes[i] * primes[i+1]);
    }
    std::sort(mult.begin(), mult.end());

    int n;
    scanf("%d", &n);
    printf("%d", *std::upper_bound(mult.begin(), mult.end(), n));

    return 0;
}