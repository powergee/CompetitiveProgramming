#include <iostream>
#include <string>
#define MOD 998244353

typedef long long Long;
typedef __int128_t BigInt;

int main() {
    Long n;
    scanf("%lld", &n);

    if (n <= 9) {
        printf("%lld", n*(n+1)/2);
        return 0;
    }

    Long result = 45;
    auto nStr = std::to_string(n);
    BigInt sumLast = 90;
    for (int i = 2; i < nStr.size(); ++i) {
        // 10 ~ 99 : sum(1, 90)
        // 100 ~ 999 : sum(1, 900)
        // ...
        // 10^(i-1) ~ 10^i - 1 : sum(1, 9*10^(i-1))
        result += (sumLast*(sumLast+1)/2) % MOD;
        sumLast *= 10;
        result %= MOD;
    }

    sumLast = n-sumLast/9+1;
    result += (sumLast*(sumLast+1)/2) % MOD;
    result %= MOD;

    printf("%lld", result);

    return 0;
}