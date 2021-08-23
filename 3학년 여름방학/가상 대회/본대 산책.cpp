#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdarg>
#define MOD 1000000007

typedef long long Long;

int main() {
    int dMax;
    scanf("%d", &dMax);

    Long prev[8], curr[8];
    std::fill(prev, prev+8, 0);
    prev[0] = 1;

    for (int d = 1; d <= dMax; ++d) {
        std::fill(curr, curr+8, 0);
        curr[0] = (prev[1] + prev[2]) % MOD;
        curr[1] = (prev[0] + prev[2] + prev[3]) % MOD;
        curr[2] = (prev[0] + prev[1] + prev[3] + prev[4]) % MOD;
        curr[3] = (prev[1] + prev[2] + prev[4] + prev[5]) % MOD;
        curr[4] = (prev[2] + prev[3] + prev[5] + prev[6]) % MOD;
        curr[5] = (prev[3] + prev[4] + prev[7]) % MOD;
        curr[6] = (prev[4] + prev[7]) % MOD;
        curr[7] = (prev[5] + prev[6]) % MOD;
        std::copy(curr, curr+8, prev);
    }

    printf("%lld", prev[0]);

    return 0;
}