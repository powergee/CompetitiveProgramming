#include <iostream>

typedef long long Long;

const Long MAX = 400001;
const Long MOD = 998244353;
Long fact[MAX+1];

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        Long pow = getModPow(val, exp/2);
        return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
    }
}

Long getModInverse(Long val) {
    return getModPow(val, MOD-2);
}

Long getComb(Long n, Long k) {
    if (n < k) {
        return 0;
    }

    return (fact[n] * getModInverse((fact[n-k]*fact[k]) % MOD)) % MOD;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i) {
        fact[i] = (fact[i-1]*i) % MOD;
    }

    Long A, B, K;
    scanf("%lld %lld %lld", &A, &B, &K);

    Long answer = 1;
    for (int k = 1; k <= K; ++k) {
        Long curr = getComb(A, k) * getComb(B, k);
        curr %= MOD;
        answer += curr;
        answer %= MOD;
    }
    printf("%lld", answer);

    return 0;
}