typedef long long Long;
const Long MOD = 1000000007;

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

Long getComb(Long n, Long k) {
    Long num = 1, den = 1;
    for (int i = 0; i < k; ++i) {
        num *= n-i;
        num %= MOD;
        den *= i+1;
        den %= MOD;
    }
    Long result = num * getInverse(den, MOD) % MOD;
    return result;
}