#include <iostream>
#include <algorithm>
#include <valarray>

typedef long long Long;

std::valarray<Long> countDigits(Long val) {
    std::valarray<Long> result(10);
    for (char ch : std::to_string(val)) {
        result[ch-'0']++;
    }
    return result;
}

std::valarray<Long> countDigits(Long start, Long end, Long exp = 1) {
    std::valarray<Long> result(10);
    while (start % 10 != 0 && start <= end) {
        result += countDigits(start++) * exp;
    }
    while (end % 10 != 9 && start <= end) {
        result += countDigits(end--) * exp;
    }
    if (start < end && start % 10 == 0 && end % 10 == 9) {
        result += (end/10-start/10+1) * exp;
        result += countDigits(start/10, end/10, exp*10);
    }
    return result;
}

int main() {
    Long n;
    scanf("%lld", &n);
    for (Long c : countDigits(1, n)) {
        printf("%lld ", c);
    }
    return 0;
}
