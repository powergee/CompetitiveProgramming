#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#define MAX 40000
#define MOD 1000000007

typedef long long Long;

int main() {
    // 498 integers
    std::vector<int> palins;
    for (int i = 1; i <= MAX; ++i) {
        std::string digits = std::to_string(i);
        bool valid = true;
        for (int j = 0; j < digits.size(); ++j) {
            if (digits[j] != digits[digits.size()-1-j]) {
                valid = false;
            }
        }
        if (valid) {
            palins.push_back(i);
        }
    }

    std::vector<std::vector<Long>> dp(MAX+1, std::vector<Long>(palins.size()+1, -1));
    dp[0][palins.size()] = 1;
    for (int sum = 1; sum <= MAX; ++sum) {
        dp[sum][palins.size()] = 0;
    }
    for (int pIdx = palins.size()-1; pIdx >= 0; --pIdx) {
        for (int sum = 0; sum <= MAX; ++sum) {
            dp[sum][pIdx] = dp[sum][pIdx+1];
            if (palins[pIdx] <= sum) {
                dp[sum][pIdx] += dp[sum-palins[pIdx]][pIdx];
                dp[sum][pIdx] %= MOD;
            }
        }
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%lld\n", dp[n][0]);
    }

    return 0;
}