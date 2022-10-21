#include <iostream>
#include <numeric>

typedef long long Long;

int main() {
    const Long MOD = 1000000007;
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        Long n;
        std::cin >> n;

        Long answer = 0, lcm = 1;
        for (Long curr = 2; lcm <= n+1; ++curr) {
            answer += ((n/lcm - n/(std::lcm(lcm, curr))) * curr) % MOD;
            answer %= MOD;
            lcm = std::lcm(lcm, curr);
        }

        std::cout << answer << "\n";
    }

    return 0;
}