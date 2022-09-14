#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
#include <valarray>

typedef long long Long;
typedef __int128_t BigInt;
typedef std::valarray<Long> Quadruple;

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

// Heron's Method
Long getIntSqrt(Long n) {
    if (n <= 1) {
        return n;
    }

    Long x0 = n;
    Long x1 = std::min(1LL<<((64-__builtin_clzll(n))/2+1), n/2);
    while (x1 < x0) {
        x0 = x1;
        x1 = (x0 + n/x0) / 2;
    }
    return x0;
}

bool isPerfectSquare(Long n) {
    Long sqrt = getIntSqrt(n);
    return sqrt * sqrt == n;
}

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

// Brahmagupta–Fibonacci identity
Quadruple mergeAsTwo(Quadruple a, Quadruple b) {
    return std::abs(Quadruple {
        a[0]*b[0] - a[1]*b[1],
        a[0]*b[1] + a[1]*b[0],
        0, 0
    });
}

std::vector<Long> getRemainders(Long a, Long b, Long bound) {
    Long boundSqrt = getIntSqrt(bound);
    std::vector<Long> result;
    while (b != 0) {
        Long r = a % b;
        if (r <= boundSqrt) {
            result.push_back(r);
        }
        a = b;
        b = r;
    }
    return result;
}

// p is one or a prime number (1 or 2 or 4k+1)
Quadruple findSumOfTwo(Long p) {
    if (p == 1) {
        return { 1, 0, 0, 0 };
    }
    if (p == 2) {
        return { 1, 1, 0, 0 };
    }
    std::vector<Long> rems;
    do {
        Long q = rand() % p;
        while (getModPow(q, (p-1)/2, p) != p-1) {
            q = rand() % p;
        }

        Long x = getModPow(q, (p-1)/4, p);
        rems = getRemainders(p, x, p);
    } while (rems.size() <= 2);
    return { rems[0], rems[1], 0, 0 };
}

const std::map<Long, Quadruple> RABIN_EXCEPTIONS = {
    { 5, { 2, 1, 0, 0 } },
    { 10, { 3, 1, 0, 0 } },
    { 13, { 3, 2, 0, 0 } },
    { 34, { 5, 3, 0, 0 } },
    { 37, { 6, 1, 0, 0 } },
    { 58, { 7, 3, 0, 0 } },
    { 61, { 6, 5, 0, 0 } },
    { 85, { 9, 2, 0, 0 } },
    { 130, { 11, 3, 0, 0 } },
    { 214, { 14, 3, 3, 0 } },
    { 226, { 15, 1, 0, 0 } },
    { 370, { 19, 3, 0, 0 } },
    { 526, { 21, 9, 2, 0 } },
    { 706, { 25, 9, 0, 0 } },
    { 730, { 27, 1, 0, 0 } },
    { 829, { 27, 10, 0, 0 } },
    { 1414, { 33, 18, 1, 0 } },
    { 1549, { 35, 18, 0, 0 } },
    { 1906, { 41, 15, 0, 0 } },
    { 2986, { 45, 31, 0, 0 } },
    { 7549, { 85, 18, 0, 0 } },
    { 9634, { 97, 15, 0, 0 } },
};

// MICHAEL 0. RABIN et al. "Randomized Algorithms in Number Theory"
Quadruple findSumOfThree(Long n) {
    if (RABIN_EXCEPTIONS.find(n) != RABIN_EXCEPTIONS.end()) {
        return RABIN_EXCEPTIONS.at(n);
    } else if (n % 4 == 0) {
        return findSumOfThree(n/4)*2;
    } else if (n % 8 == 7) {
        return { 0, 0, 0, 0 }; // Exception - Impossible
    } else if (n % 8 == 3) {
        Long x, p;
        do {
            x = rand() % (getIntSqrt(n)+1);
            p = (n - x*x) / 2;
        } while ((n-x*x) % 2 != 0 || !(isPrime(p) || p == 1));
        auto two = findSumOfTwo(p);
        return { x, two[0]+two[1], std::abs(two[0]-two[1]), 0 };
    } else if (isPerfectSquare(n)) {
        return { getIntSqrt(n), 0, 0, 0 };
    } else {
        Long x, p;
        do {
            x = rand() % (getIntSqrt(n)+1);
            p = (n - x*x);
        } while (!isPrime(p));
        auto two = findSumOfTwo(p);
        return { x, two[0], two[1], 0 };
    }
}

Quadruple findSolution(Long n) {
    if (n == 1) {
        return { 1, 0, 0, 0 };
    } else if (n == 2) {
        return { 1, 1, 0, 0 };
    } else if (n == 3) {
        return { 1, 1, 1, 0 };
    }

    // n이 4의 배수라면 이를 제거해줌.
    // 아래에서 n = 4^a mod 8 = 7 인지 체크하여 4개의 수가 필요한지를 체크하기 때문.
    if (n % 4 == 0) {
        return findSolution(n/4) * 2;
    }
    
    // 완전 제곱수라면 1개로 표현. (필요충분)
    if (isPerfectSquare(n)) {
        return { getIntSqrt(n), 0, 0, 0 };
    }

    // n mod 8 = 7 이라면 무조건 4개의 수가 필요. (필요충분)
    // n = 4 + (n-4)로 분할하면 (n-4) mod 8 = 3 이므로 3개 내로 표현 가능할 테고,
    // 그럼 { 2, solution of (n-4) }가 해가 될 것.
    if (n % 8 == 7) {
        auto sub = findSumOfThree(n-4);
        return { 2, sub[0], sub[1], sub[2] };
    }

    auto primes = factorize(n);
    Long evenAcc = 1;
    // oddCount에 들어가는 것은 지수가 홀수인 소인수.
    std::set<Long> oddCount;
    for (Long p : primes) {
        if (oddCount.find(p) == oddCount.end()) {
            oddCount.insert(p);
        } else {
            evenAcc *= p;
            oddCount.erase(p);
        }
    }

    // n mod 8 != 7 이라면 2개 or 3개로 만들 수 있음.
    // oddCount에 포함된 p에는 2 or 4k+1 꼴 or 4k+3 꼴의 소수가 있을 수 있는데
    // 2와 4k+1은 2개의 제곱수로 나타낼 수 있으나,
    // 4k+3는 3개의 제곱수 필요.
    bool mod3Exist = false;
    for (Long p : oddCount) {
        if (p % 4 == 3) {
            mod3Exist = true;
        }
    }

    if (mod3Exist) {
        return findSumOfThree(n);
    }

    auto result = findSumOfTwo(*oddCount.begin());
    for (auto it = std::next(oddCount.begin()); it != oddCount.end(); ++it) {
        result = mergeAsTwo(result, findSumOfTwo(*it));
    }
    return result * evenAcc;
}

int main() {
    Long n;
    scanf("%lld", &n);
    auto result = findSolution(n);
    std::vector<Long> comp;
    for (int i = 0; i < 4; ++i) {
        if (result[i]) {
            comp.push_back(result[i]);
        }
    }

    printf("%d\n", int(comp.size()));
    for (Long s : comp) {
        printf("%lld ", s);
    }
    return 0;
}