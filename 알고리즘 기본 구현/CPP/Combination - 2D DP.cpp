#define MOD 1000000007

typedef long long Long;

Long comb[4001][4001];

Long calcComb(int n, int k) {
    if (n < k) {
        return 0;
    } else if (k == 0) {
        return 1;
    } else if (comb[n][k] != -1) {
        return comb[n][k];
    }
    return comb[n][k] = ((calcComb(n-1, k-1) + calcComb(n-1, k)) % MOD);
}