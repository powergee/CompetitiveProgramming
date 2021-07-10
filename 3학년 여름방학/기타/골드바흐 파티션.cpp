#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

bool isPrime[1000001];

int main() {
    std::fill(isPrime, isPrime+1000001, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i*i < 1000001; ++i) {
        if (isPrime[i]) {
            for (int j = i*i; j < 1000001; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::set<int> primes;
    for (int i = 2; i < 1000001; ++i) {
        if (isPrime[i]) {
            primes.insert(i);
        }
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        int n, answer = 0;
        scanf("%d", &n);

        for (int p : primes) {
            if (n < 2*p) {
                break;
            }
            int spare = n - p;
            if (primes.find(spare) != primes.end()) {
                ++answer;
            }
        }
        printf("%d\n", answer);
    }

    return 0;
}