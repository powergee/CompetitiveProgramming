#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <numeric>
#include <array>
#include <queue>
#include <map>
#include <set>

using Long = long long;
using BigInt = __int128_t;

struct IO {
    IO() {
        std::cin.tie(nullptr)->sync_with_stdio(false);
    }

    template<typename T>
    T scan() {
        T result;
        std::cin >> result;
        return result;
    }

    int scanInt() { return scan<int>(); }
    Long scanLong() { return scan<Long>(); }
    double scanDouble() { return scan<double>(); }
    std::string scanToken() { return scan<std::string>(); }

    template<typename T>
    std::vector<T> scans(int n) {
        std::vector<T> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = scan<T>();
        }
        return arr;
    }

    std::vector<int> scanInts(int n) { return scans<int>(n); }
    std::vector<Long> scanLongs(int n) { return scans<Long>(n); }
    std::vector<double> scanDoubles(int n) { return scans<double>(n); }
    std::vector<std::string> scanTokens(int n) { return scans<std::string>(n); }

    template<typename T, unsigned int N>
    std::array<T, N> scans() {
        std::array<T, N> result;
        for (int i = 0; i < N; ++i) {
            result[i] = scanInt();
        }
        return result;
    }

    template<unsigned int N> std::array<int, N> scanInts() { return scans<int, N>(); }
    template<unsigned int N> std::array<Long, N> scanLongs() { return scans<Long, N>(); }
    template<unsigned int N> std::array<double, N> scanDoubles() { return scans<double, N>(); }
    template<unsigned int N> std::array<std::string, N> scanTokens() { return scans<std::string, N>(); }

    std::vector<std::vector<int>> scanMatrix(int r, int c) {
        std::vector<std::vector<int>> result(r, std::vector<int>(c));
        for (int i = 0; i < r; ++i) {
            result[i] = scanInts(c);
        }
        return result;
    }

    template<typename T>
    void print(T value) {
        std::cout << value << " ";
    }

    template<typename T, typename... Args>
    void print(T value, Args... args) {
        std::cout << value << " ";
        print(args...);
    }

    void printLine() {
        std::cout << "\n";
    }

    template<typename T>
    void printLine(T value) {
        std::cout << value << "\n";
    }

    template<typename T, typename... Args>
    void printLine(T value, Args... args) {
        std::cout << value << " ";
        printLine(args...);
    }

    void untilEOF(std::function<void()> solve) {
        while (std::cin.eof() != false) {
            solve();
        }
    }

    void codeforces(std::function<void()> solve) {
        int T = scanInt();
        while (T--) {
            solve();
        }
    }

    void google(std::function<void()> solve) {
        int T = scanInt();
        for (int t = 1; t <= T; ++t) {
            std::cout << "Case #" << t << ": ";
            solve();
        }
    }
};

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
    IO io;
    Long n = io.scanLong();

    std::vector<Long> squares;
    squares.reserve(n);
    for (int i = 1; i*i <= n; ++i) {
        squares.push_back(i*i);
    }

    Long answer = 0;
    for (Long a = 1; a <= n; ++a) {
        auto primes = factorize(a);
        std::map<Long, int> count;
        Long mult = 1;
        for (Long p : primes) {
            count[p]++;
        }
        for (auto [p, cnt] : count) {
            if (cnt % 2) {
                mult *= p;
            }
        }
        Long left = 0, right = int(squares.size())-1;
        while (left+1 < right) {
            Long mid = (left+right) / 2;
            if (squares[mid]*mult <= n) {
                left = mid;
            } else {
                right = mid-1;
            }
        }
        if (squares[right]*mult <= n) {
            left = right;
        }
        answer += left+1;
    }
    io.printLine(answer);

    return 0;
}