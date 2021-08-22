#include <iostream>
#include <numeric>
#include <set>

long long arr[100000];
bool isCoprime[100001];

std::set<int> getPrimes(long long val) {
    std::set<int> result;
    long long curr = val;
    for (long long div = 2; div*div <= val && curr > 1;) {
        if (curr % div == 0) {
            result.insert(div);
            curr /= div;
        } else {
            ++div;
        }
    }
    if (curr > 1) {
        result.insert(curr);
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::fill(isCoprime, isCoprime+m+1, true);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", arr+i);
        auto primes = getPrimes(arr[i]);
        for (long long p : primes) {
            if (isCoprime[p]) {
                for (long long i = p; i <= m; i += p) {
                    isCoprime[i] = false;
                }
            }
        }
    }

    int count = 0;
    for (int i = 1; i <= m; ++i) {
        if (isCoprime[i]) {
            ++count;
        }
    }

    printf("%d\n", count);
    for (int i = 1; i <= m; ++i) {
        if (isCoprime[i]) {
            printf("%d\n", i);
        }
    }

    return 0;
}