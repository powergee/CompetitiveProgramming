#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

typedef long long Long;

Long intRem[100][51];
Long strRem[15];

int getRemainder(std::string n, int mod) {
    int result = 0, pow = 1;
    for (int i = 0; i < n.size(); ++i) {
        result += ((n[n.size()-1-i]-'0') * pow) % mod;
        result %= mod;
        pow *= 10;
        pow %= mod;
    }
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    int maxLength = 0;
    std::vector<std::string> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
        maxLength = std::max(maxLength, int(numbers[i].size()));
    }

    int k;
    std::cin >> k;

    for (int i = 0; i < k; ++i) {
        intRem[i][0] = i % k;
        for (int j = 1; j <= maxLength; ++j) {
            intRem[i][j] = (intRem[i][j-1] * 10) % k;
        }
    }
    for (int i = 0; i < n; ++i) {
        strRem[i] = getRemainder(numbers[i], k);
    }

    std::vector<std::vector<std::pair<Long, Long>>> dp(1<<n, std::vector<std::pair<Long, Long>>(k, {-1, -1}));
    std::function<std::pair<Long, Long>(int, int)> countCases = [&](int used, int rem) -> std::pair<Long, Long> {
        std::pair<Long, Long>& result = dp[used][rem];
        if (result.first != -1) {
            return result;
        }
        if (used == (1<<n)-1) {
            return result = (rem == 0 ? std::make_pair(1, 1) : std::make_pair(0, 1));
        }

        result = {0, 0};
        for (int i = 0; i < n; ++i) {
            if ((used & (1<<i)) == 0) {
                int nextRem = (intRem[rem][numbers[i].size()] + strRem[i]) % k;
                auto sub = countCases(used|(1<<i), nextRem);
                result.first += sub.first;
                result.second += sub.second;
            }
        }

        return result;
    };

    auto result = countCases(0, 0);
    
    if (result.first == 0) {
        std::cout << "0/1";
    } else {
        Long gcd = std::gcd(result.first, result.second);
        std::cout << result.first/gcd << "/" << result.second/gcd;
    }

    return 0;
}