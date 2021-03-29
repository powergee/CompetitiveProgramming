#include <iostream>
#include <algorithm>

typedef long long Long;

Long countParticles(int decay, int remain);
Long sumParticles(int decay, int remainLeft);

const Long MOD = 1000000007LL;
Long countDp[1001][1001];
Long sumDp[1001][1001];
int n, k;

Long countParticles(int decay, int remain) {
    Long& result = countDp[decay][remain];
    if (result != -1) {
        return result;
    }

    result = 1;
    if (decay != 1 && remain >= 1) {
        result += sumParticles(decay - 1, n - remain);
        result %= MOD;
    }

    return result;
}

Long sumParticles(int decay, int remainLeft) {
    if (remainLeft < 0 || n <= remainLeft) {
        return 0;
    }

    Long& result = sumDp[decay][remainLeft];
    if (result != -1) {
        return result;
    }

    result = countParticles(decay, remainLeft);
    if (remainLeft < n-1) {
        result += sumParticles(decay, remainLeft + 1);
        result %= MOD;
    }

    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    std::fill(&countDp[0][0], &countDp[0][0] + sizeof(countDp) / sizeof(Long), -1LL);
    std::fill(&sumDp[0][0], &sumDp[0][0] + sizeof(sumDp) / sizeof(Long), -1LL);
    while (T--) {
        scanf("%d %d", &n, &k);
        printf("%lld\n", countParticles(k, n));

        for (int i = 0; i <= k; ++i) {
            std::fill(countDp[i], countDp[i] + n + 1, -1LL);
            std::fill(sumDp[i], sumDp[i] + n + 1, -1LL);
        }
    }
}