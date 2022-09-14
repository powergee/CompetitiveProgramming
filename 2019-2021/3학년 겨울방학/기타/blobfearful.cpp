#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

typedef long long Long;

std::map<Long, int> factorize(Long val) {
    Long p = 2;
    std::map<Long, int> result;
    while (p*p <= val) {
        if (val % p == 0) {
            result[p]++;
            val /= p;
        } else {
            p++;
        }
    }
    if (val > 1) {
        result[val]++;
    }
    return result;
}

Long getPower(Long base, int exp) {
    Long result = 1, subPower = base;
    while (exp) {
        if (exp & 1) {
            result *= subPower;
        }
        exp /= 2;
        subPower *= subPower;
    }
    return result;
}

Long findLeastFactorial(Long base, int exp) {
    Long pow = getPower(base, exp);
    Long left = 1, right = pow;
    while (left < right) {
        Long mid = (left+right)/2;
        
        Long count = 0, coeff = base, coeffExp = 1;
        while (coeffExp <= exp) {
            count += mid / coeff;
            coeff *= base;
            coeffExp++;
        }

        if (count < exp) {
            left = mid+1;
        } else {
            right = mid;
        }
    }
    return left;
}

int main() {
    Long k, q;
    scanf("%lld %lld", &k, &q);

    auto factors = factorize(k);
    for (int i = 0; i < q; ++i) {
        Long a;
        scanf("%lld", &a);

        auto currFactors = factors;
        for (auto [base, _] : factors) {
            while (a % base == 0 && currFactors[base] > 0) {
                currFactors[base]--;
                a /= base;
            }
        }
        Long result = 1;
        for (auto [base, exp] : currFactors) {
            if (currFactors[base] <= 0) {
                continue;
            }
            result = std::max(result, findLeastFactorial(base, exp));
        }
        printf("%lld ", result);
    }

    return 0;
}