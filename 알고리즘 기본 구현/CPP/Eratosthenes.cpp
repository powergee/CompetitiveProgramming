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

// Slower
std::vector<int> getPrimes(int first, int last) {
    first = std::max(first, 2);
    int count = last - first + 1;
    std::vector<bool> isPrime(count, true);
    std::vector<int> primes;

    for (int div = 2; div*div <= last; ++div) {
        int fillStart = -1;
        for (int i = std::max(0, div - first); i < count; ++i) {
            if (isPrime[i] && (first + i) % div == 0) {
                fillStart = first + i;
                break;
            }
        }

        if (fillStart != -1) {
            for (int i = std::max(div*div, fillStart) - first; i < count; i += div) {
                isPrime[i] = false;
            }
        }
    }

    for (int i = 0; i < count; ++i) {
        if (isPrime[i]) {
            primes.push_back(i + first);
        }
    }

    return primes;
}