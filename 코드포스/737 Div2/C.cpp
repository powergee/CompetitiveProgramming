#include <iostream>
#include <algorithm>
#define MOD 1000000007

typedef long long Long;

int n, k;
Long dp[200000];

Long getNegMod(Long val) {
    if (val >= 0) {
        return val % MOD;
    }
    return getNegMod(val+MOD);
}

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

Long countCases(int i) {
    if (i == k) {
        return 1;
    }

    if (dp[i] != -1) {
        return dp[i];
    }

    dp[i] = 0;
    if (n % 2 == 0) {
        dp[i] += getModPow(2, (Long)n*(k-i-1));
    } else {
        dp[i] += countCases(i+1);
    }
    dp[i] %= MOD;

    if (n % 2 == 0) {
        dp[i] += getNegMod(getModPow(2, n-1)-1) * countCases(i+1);
    } else {
        dp[i] += getModPow(2, n-1) * countCases(i+1);
    }
    dp[i] %= MOD;

    return dp[i];
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d", &n, &k);

        if (k == 0) {
            printf("1\n");
        } else {
            std::fill(dp, dp+k, -1LL);
            printf("%lld\n", countCases(0));
        }
    }

    return 0;
}