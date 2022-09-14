#include <iostream>
#include <vector>
#include <set>

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
    auto primes = getPrimes(1000);
    std::set<int> pSet(primes.begin(), primes.end());

    int n, count = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int p;
        scanf("%d", &p);
        if (pSet.find(p) != pSet.end()) {
            ++count;
        }
    }

    printf("%d", count);
}