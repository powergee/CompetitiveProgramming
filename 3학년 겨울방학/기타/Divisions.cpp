#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

typedef long long Long;
typedef __int128_t BigInt;

const std::vector<std::pair<Long, std::vector<int>>> TEST_SET = {
    { 2'047LL, { 2 } },
    { 1'373'653LL, { 2, 3 } },
    { 9'080'191LL, { 31, 73 } },
    { 25'326'001LL, { 2, 3, 5 } },
    { 3'215'031'751LL, { 2, 3, 5, 7 } },
    { 4'759'123'141LL, { 2, 7, 61 } },
    { 1'122'004'669'633LL, { 2, 13, 23, 1662803 } },
    { 2'152'302'898'747LL, { 2, 3, 5, 7, 11 } },
    { 3'474'749'660'383LL, { 2, 3, 5, 7, 11, 13 } },
    { 341'550'071'728'321LL, { 2, 3, 5, 7, 11, 13, 17 } },
    { 3'825'123'056'546'413'051LL, { 2, 3, 5, 7, 11, 13, 17, 19, 23 } },
    { 0LL, { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 } }
};

BigInt getModPow(Long val, Long exp, Long mod) {
    BigInt result = 1, subPower = val % mod;
    while (exp) {
        if (exp % 2 == 1) {
            result = (result * subPower) % mod;
        }
        exp /= 2;
        subPower = (subPower * subPower) % mod;
    }
    return result;
}

bool testMillerRabin(Long n, const std::vector<int>& tests) {
    for (int a : tests) {
        Long d = n-1;
        while (d % 2 == 0) {
            d /= 2;
        }
        bool passed = false;
        BigInt x = getModPow(a, d, n);
        if (x == 1 || x == n-1) {
            passed = true;
        }
        while (d != n-1 && !passed) {
            x = (x*x) % n;
            d *= 2;
            if (x == n-1) {
                passed = true;
            }
        }
        if (!passed) {
            return false;
        }
    }
    return true;
}

bool isPrime(Long n) {
    if (n == 2) {
        return true;
    } else if (n <= 1 || n % 2 == 0) {
        return false;
    }
    for (auto [bound, tests] : TEST_SET) {
        if (n < bound) {
            return testMillerRabin(n, tests);
        }
    }
    return testMillerRabin(n, TEST_SET.back().second);
}

void factorize(Long n, std::vector<Long>& result) {
    if (n <= 1) {
        return;
    } else if (isPrime(n)) {
        result.push_back(n);
        return;
    } else if (n % 2 == 0) {
        result.push_back(2);
        factorize(n/2, result);
        return;
    }

    Long xs, xt, factor = n, c;
    auto f = [&](Long x) -> Long {
        return (BigInt(x)*x % n + c) % n;
    };

    do {
        if (factor == n) {
            xs = xt = rand() % (n-2) + 2;
            c = rand() % 20 + 1;
        }
        xs = f(xs);
        xt = f(f(xt));
        factor = std::gcd(std::abs(xs-xt), n);
    } while (factor == 1);

    factorize(factor, result);
    factorize(n/factor, result);
}

std::vector<Long> factorize(Long n) {
    std::vector<Long> result;
    factorize(n, result);
    std::sort(result.begin(), result.end());
    return result;
}

int main() {
    Long n;
    scanf("%lld", &n);

    auto factors = factorize(n);
    std::map<Long, int> count;
    for (Long f : factors) {
        count[f]++;
    }

    Long result = 1;
    for (auto p : count) {
        result *= p.second+1;
    }
    printf("%lld", result);

    return 0;
}