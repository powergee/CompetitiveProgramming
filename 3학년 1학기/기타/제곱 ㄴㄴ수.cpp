#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int countNums(Long first, Long last) {
    Long count = last - first + 1LL;
    std::vector<bool> isPrime(count, true);

    for (Long div = 2; div*div <= last; ++div) {
        Long fillStart = -1LL;
        for (Long i = std::max(0LL, div*div - first); i < count; ++i) {
            if (isPrime[i] && (first + i) % (div*div) == 0) {
                fillStart = first + i;
                break;
            }
        }

        if (fillStart != -1LL) {
            for (Long i = std::max(div*div, fillStart) - first; i < count; i += (div*div)) {
                isPrime[i] = false;
            }
        }
    }

    int answer = 0;
    for (int i = 0; i < count; ++i) {
        if (isPrime[i]) {
            ++answer;
        }
    }

    return answer;
}

int main() {
    Long min, max;
    scanf("%lld %lld", &min, &max);
    printf("%d", countNums(min, max));
    return 0;
}