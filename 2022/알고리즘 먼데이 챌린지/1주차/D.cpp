#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;
    std::vector<int> primes;

    for (int div = 2; div*div <= n; ++div) {
        if (isPrime[div]) {
            for (int i = div*div; i <= n; i += div) {
                isPrime[i] = false;
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        int v;
        std::cin >> v;
        if (isPrime[i]) {
            answer += v;
        }
    }

    std::cout << answer;

    return 0;
}