#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define MOD 998244353LL

typedef long long Long;

Long factorial[200001];

Long getModPow(Long val, Long exp) {
    if (val == 0) {
        return 0;
    } else if (exp == 0) {
        return 1;
    } else {
        Long pow = getModPow(val, exp/2);
        return ((((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val))) % MOD;
    }
}

Long getModDiv(Long num, Long den) {
    return ((num % MOD) * getModPow(den, MOD-2)) % MOD;
}

Long getComb(Long n, Long k) {
    // printf("getComb(%lld, %lld)\n", n, k);
    Long num = 1;
    Long den = 1;
    for (Long i = n; i >= n-k+1; --i) {
        num *= i;
        num %= MOD;
    }
    for (Long i = k; i >= 1; --i) {
        den *= i;
        den %= MOD;
    }
    // printf("num = %lld, den = %lld\n", num, den);
    return getModDiv(num, den);
}

int main() {
    factorial[0] = 1;
    for (int i = 1; i < sizeof(factorial)/sizeof(Long); ++i) {
        factorial[i] = factorial[i-1]*i;
        factorial[i] %= MOD;
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        std::vector<int> jury(n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &jury[i]);
        }

        int max = *std::max_element(jury.begin(), jury.end());
        int maxCount = 0;
        int secondMax = -1;
        int secondMaxCount = 0;
        for (int j : jury) {
            if (j == max) {
                maxCount++;
            }
            if (j < max) {
                secondMax = std::max(secondMax, j);
            }
        }

        for (int j : jury) {
            if (j == secondMax) {
                secondMaxCount++;
            }
        }

        Long answer = 0;
        if (maxCount == 1) {
            if (secondMax != -1 && max-secondMax >= 2) {
                answer = 0;
            } else {
                Long chunk = maxCount+secondMaxCount;
                // printf("chunk = %lld\n", chunk);
                answer = getComb(n, chunk);
                // printf("[%lld]\n", answer);
                answer *= (factorial[chunk-1]*(chunk-1)) % MOD;
                answer %= MOD;
                // printf("[%lld]\n", answer);
                answer *= factorial[n-chunk];
                answer %= MOD;
                // printf("[%lld]\n", answer);
            }
        } else {
            answer = factorial[n];
        }

        printf("%lld\n", answer);
    }

    return 0;
}

// 6C4 * (4!-3!) * 2! = 15 * 18 * 2 = 30*18 = 540