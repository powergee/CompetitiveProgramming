typedef long long Long;

Long getPower(Long val, Long e, Long mod) {
    if (e == 0) {
        return (val % mod) == 0 ? 0 : 1;
    } else if (e == 1) {
        return (val % mod);
    } else {
        Long sub = getPower(val, e/2, mod);
        return (((sub * sub) % mod) * ((e % 2 == 1 ? val : 1) % mod)) % mod;
    }
}
