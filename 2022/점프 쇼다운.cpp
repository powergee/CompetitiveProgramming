#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>
#include <cassert>

typedef long long Long;
const Long MOD = 1000000007LL;
Long n;
Long dp1[301];
Long dp2[301][301];
Long dp3[301][301][301];

Long countCases3(int l1, int l2, int l3);
Long countCases2(int l1, int l2);
Long countCases1(int l1);

Long countCases3(int l1, int l2, int l3) {
    assert(l1 != 0 && l2 != 0 && l3 != 0);
    auto& result = dp3[l1][l2][l3];
    if (result != -1) {
        return result;
    }
    if (l1+l2+l3 == 3) {
        return result = 1;
    }
    result = 0;
    if (l1 >= 2) {
        result += 2*countCases3(l1-1, l2, l3);
        result %= MOD;
    }
    if (l2 >= 2) {
        result += 2*countCases3(l1, l2-1, l3);
        result %= MOD;
    }
    if (l3 >= 2) {
        result += 2*countCases3(l1, l2, l3-1);
        result %= MOD;
    }
    return result;
}

Long countCases2(int l1, int l2) {
    assert(l1 != 0 && l2 != 0);
    auto& result = dp2[l1][l2];
    if (result != -1) {
        return result;
    }
    if (l1+l2 == 3) {
        return result = 1;
    }
    result = 0;
    if (l1 >= 2) {
        result += 2*countCases2(l1-1, l2);
        result %= MOD;
    }
    if (l2 >= 2) {
        result += 2*countCases2(l1, l2-1);
        result %= MOD;
    }

    for (int l3 = 1; l1-l3 >= 2; ++l3) {
        result += countCases3(l3, l1-l3-1, l2);
        result %= MOD;
    }
    for (int l3 = 1; l2-l3 >= 2; ++l3) {
        result += countCases3(l3, l2-l3-1, l1);
        result %= MOD;
    }
    return result;
}

Long countCases1(int l1) {
    assert(l1 != 0);
    if (dp1[l1] != -1) {
        return dp1[l1];
    }
    if (l1 == 3) {
        return dp1[l1] = 1;
    }
    dp1[l1] = 2*countCases1(l1-1);
    dp1[l1] %= MOD;
    for (int l2 = 1; l1-l2 >= 2; ++l2) {
        dp1[l1] += countCases2(l1-l2-1, l2);
        dp1[l1] %= MOD;
    }
    return dp1[l1];
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;

    std::fill(dp1, dp1+sizeof(dp1)/sizeof(Long), -1);
    std::fill(&dp2[0][0], &dp2[0][0]+sizeof(dp2)/sizeof(Long), -1LL);
    std::fill(&dp3[0][0][0], &dp3[0][0][0]+sizeof(dp3)/sizeof(Long), -1LL);

    std::cout << (n*countCases1(n-1) % MOD);

    return 0;
}