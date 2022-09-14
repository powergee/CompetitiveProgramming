#include <iostream>

typedef long long Long;

const Long MAX = 4000000;
const Long MOD = 1000000007;
Long fact[MAX+1];

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        long pow = getModPow(val, exp/2);
        return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
    }
}

Long getModInverse(Long val) {
    return getModPow(val, MOD-2);
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i) {
        fact[i] = (fact[i-1]*i) % MOD;
    }

    int q;
    scanf("%d", &q);

    while (q--) {
        Long n, k;
        scanf("%lld %lld", &n, &k);
        printf("%lld\n", (fact[n] * getModInverse((fact[n-k]*fact[k]) % MOD)) % MOD);
    }

    return 0;
}