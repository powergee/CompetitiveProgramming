#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;
typedef __int128_t BigInt;

std::vector<BigInt> getPrimes(int last) {
    if (last < 2) {
        return std::vector<BigInt>();
    }

    std::vector<bool> isPrime(last + 1, true);
    isPrime[0] = isPrime[1] = false;
    std::vector<BigInt> primes;

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
    auto primes = getPrimes(1000000);
    Long n;
    scanf("%lld", &n);

    auto pow3 = [](BigInt v) { return v*v*v; };

    Long answer = 0;
    for (int i = 0; i+1 < primes.size(); ++i) {
        BigInt p = primes[i];
        if (n < p * pow3(primes[i+1])) { break; }

        int left = i+1, right = primes.size()-1;
        while (left+1 < right) {
            int mid = (left+right) / 2;
            BigInt mult = p * pow3(primes[mid]);
            if (mult <= n) {
                left = mid;
            } else {
                right = mid-1;
            }
        }
        if (p * pow3(primes[right]) <= n) {
            left = right;
        }
        answer += left-i;
    }

    printf("%lld", answer);

    return 0;
}