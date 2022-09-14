#include <iostream>
#include <algorithm>
#include <vector>

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

std::vector<int> primes = getPrimes(4000000);
std::vector<long long> pSum;

int main() {
    pSum.resize(primes.size(), 0);
    pSum[0] = primes[0];
    for (int i = 1; i < primes.size(); ++i) {
        pSum[i] = pSum[i-1] + primes[i];
    }

    long long n;
    scanf("%lld", &n);

    int answer = 0;
    for (int i = 0; i < pSum.size(); ++i) {
        if (n < primes[i]) {
            break;
        }
        long long valToFound = n + (i==0 ? 0 : pSum[i-1]);
        auto found = std::lower_bound(pSum.begin(), pSum.end(), valToFound);
        if (found != pSum.end() && *found == valToFound) {
            ++answer;
        }
    }

    printf("%d", answer);
    return 0;
}