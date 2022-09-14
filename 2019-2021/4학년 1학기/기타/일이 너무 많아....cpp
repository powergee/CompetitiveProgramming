#include <iostream>
#include <string>
#include <vector>
#include <functional>

typedef long long Long;
typedef __int128_t BigInt;

Long getOnes(int length) {
    return std::stoll(std::string(length, '1'));
}

int main() {
    const std::vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17
    };
    const int pCount = primes.size();
    Long n, answer = 0;
    std::cin >> n;

    for (int mask = 1; mask < (1<<pCount); ++mask) {
        BigInt mult = 1;
        int popCount = 0;
        for (int e = 0; e < pCount && mult <= n; ++e) {
            if (mask & (1<<e)) {
                mult *= getOnes(primes[e]);
                ++popCount;
            }
        }
        answer += (n/mult) * (popCount % 2 ? 1 : -1);
    }
    
    std::cout << answer;
    return 0;
}