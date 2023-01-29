#include <vector>

typedef long long Long;

Long getComb(int n, int k, int mod) {
    if (n < k) {
        return 0;
    }

    std::vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int div = 2; div*div <= n; ++div) {
        if (isPrime[div]) {
            for (int i = div*div; i <= n; i += div) {
                isPrime[i] = false;
            }
        }
    }

    std::vector<int> primeCount(n+1, 0);
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            for (Long j = i; j <= n; j *= i) {
                primeCount[i] += n/j - k/j - (n-k)/j;
            }
        }
    }

    Long answer = 1;
    for (int i = 2; i <= n; ++i) {
        while (primeCount[i]--) {
            answer *= i;
            answer %= mod;
        }
    }
    return answer;
}