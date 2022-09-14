#include <iostream>
#include <vector>
#include <map>

typedef long long Long;

struct PowerNumber {
    Long val;
    Long base;
    int exp;
};

Long getPower(Long val, int e) {
    Long result = 1;
    while (e--) {
        if (result > (long double)INT64_MAX / val) {
            result = INT64_MAX;
            break;
        }
        result *= val;
    }
    return result;
}

std::vector<PowerNumber> findLowerPower(Long pivot) {
    std::vector<PowerNumber> result;
    for (int e = 2; e <= 62; ++e) {
        Long left = 2, right = 1e9;
        if (pivot < getPower(left, e)) {
            break;
        }
        while (left+1 < right) {
            Long med = (left + right) / 2;
            if (getPower(med, e) <= pivot) {
                left = med;
            } else {
                right = med-1;
            }
        }
        if (getPower(right, e) <= pivot) {
            result.push_back({ getPower(right, e), right, e });
        } else {
            result.push_back({ getPower(left, e), left, e });
        }
    }
    return result;
}

std::vector<PowerNumber> findUpperPower(Long pivot) {
    std::vector<PowerNumber> result;
    for (int e = 2; e <= 62; ++e) {
        Long left = 2, right = 1e9;
        if (getPower(right, e) <= pivot) {
            break;
        }
        while (left < right) {
            Long med = (left + right) / 2;
            if (getPower(med, e) <= pivot) {
                left = med+1;
            } else {
                right = med;
            }
        }
        result.push_back({ getPower(left, e), left, e });
    }
    return result;
}

std::map<Long, Long> dp;

Long getMinMoves(Long n) {
    if (dp.find(n) != dp.end()) {
        return dp[n];
    }

    dp[n] = n-1;
    auto lower = findLowerPower(n);
    auto upper = findUpperPower(n);

    for (PowerNumber neigh : lower) {
        if (neigh.val != INT64_MAX) {
            dp[n] = std::min(dp[n], getMinMoves(neigh.base) + std::abs(neigh.val-n) + 1);
        }
    }
    for (PowerNumber neigh : upper) {
        if (neigh.val != INT64_MAX) {
            dp[n] = std::min(dp[n], getMinMoves(neigh.base) + std::abs(neigh.val-n) + 1);
        }
    }

    return dp[n];
}

int main() {
    Long n;
    scanf("%lld", &n);
    printf("%lld", getMinMoves(n));

    return 0;
}