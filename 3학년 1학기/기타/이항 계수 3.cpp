#include <iostream>
#define MOD 1000000007LL

using Long = long long;

Long getInverse(Long val, int mod) {
    Long r1 = mod, r2 = val, s1 = 1, s2 = 0, t1 = 0, t2 = 1;
    Long r, q, s, t;
    while (r2) {
        q = r1 / r2;
        r = r1 % r2;
        r1 = r2;
        r2 = r;

        s = s1 - q * s2;
        s1 = s2;
        s2 = s;

        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
    r = r1;
    s = s1;
    t = t1;
    
    if (r == 1) {
        if (t < 0) {
            t += mod;
        }
        return t;
    }
    return 0;
}

Long getModOfFactorial(int n, int mod) {
    Long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
        result %= mod;
    }

    return result;
}

int main() {
    Long n, k;
    scanf("%lld %lld", &n, &k);

    Long num = getModOfFactorial(n, MOD);
    Long den = (getModOfFactorial(k, MOD) * getModOfFactorial(n-k, MOD)) % MOD;
    Long result = num * getInverse(den, MOD) % MOD;
    
    printf("%lld", result);

    return 0;
}