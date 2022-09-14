#include <iostream>
#include <vector>
#define MOD 10007

typedef long long Long;

Long calcComb(int n, int k) {
    static std::vector<std::vector<int>> comb(53, std::vector<int>(53, -1));
    if (n < k) {
        return 0;
    } else if (k == 0) {
        return 1;
    } else if (comb[n][k] != -1) {
        return comb[n][k];
    }
    return comb[n][k] = ((calcComb(n-1, k-1) + calcComb(n-1, k)) % MOD);
}

Long getModPow(Long val, Long exp, Long mod) {
    Long result = 1, subPower = val % mod;
    while (exp) {
        if (exp % 2 == 1) {
            result = (result * subPower) % mod;
        }
        exp /= 2;
        subPower = (subPower * subPower) % mod;
    }
    return result;
}

int main() {
    int n;
    std::cin >> n;

    Long result = 0;
    for (int k = 1; 4*k <= n; ++k) {
        result += (k % 2 ? 1 : -1) * (calcComb(13, k) * calcComb(52-4*k, n-4*k));
        while (result < 0){
            result += MOD;
        }
        result %= MOD;
    }
    std::cout << result;

    return 0;
}