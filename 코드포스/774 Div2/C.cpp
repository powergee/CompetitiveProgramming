#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>

typedef long long Long;

int main() {
    std::vector<Long> factors = {
        1,
        2,
        6,
        24,
        120,
        720,
        5040,
        40320,
        362880,
        3628800,
        39916800,
        479001600,
        6227020800,
        87178291200,
        1307674368000,
    };

    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);

        Long answer = __builtin_popcountll(n);
        std::function<void(Long, int, int)> findAnswer = [&](Long val, int factEnd, int prevCount) {
            if (answer <= prevCount) {
                return;
            } else if (factEnd == -1) {
                answer = std::min(answer, (Long)__builtin_popcountll(val) + prevCount);
            } else if (val < factors[factEnd]) {
                findAnswer(val, factEnd-1, prevCount);
            } else if (val == factors[factEnd]) {
                answer = std::min(answer, (Long)prevCount+1);
            } else {
                answer = std::min(answer, (Long)__builtin_popcountll(val-factors[factEnd]) + 1 + prevCount);
                findAnswer(val-factors[factEnd], factEnd-1, prevCount + 1);
                findAnswer(val, factEnd-1, prevCount);
            }
        };
        findAnswer(n, factors.size()-1, 0);
        printf("%lld\n", answer);
    }

    return 0;
}