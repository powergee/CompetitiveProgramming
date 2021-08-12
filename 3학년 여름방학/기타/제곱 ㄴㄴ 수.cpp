#include <iostream>
#include <unordered_set>

typedef long long Long;

int main() {
    Long min, max;
    scanf("%lld %lld", &min, &max);

    std::unordered_set<Long> sqareSet;

    for (Long v = 2; v*v <= max; ++v) {
        Long firstCoeff = min / (v*v) + ((min % (v*v)) ? 1 : 0);
        for (Long c = firstCoeff; c*v*v <= max; ++c) {
            sqareSet.insert(c*v*v);
        }
    }

    Long answer = max-min+1;
    for (Long s : sqareSet) {
        if (min <= s && s <= max) {
            --answer;
        }
    }

    printf("%lld", answer);

    return 0;
}