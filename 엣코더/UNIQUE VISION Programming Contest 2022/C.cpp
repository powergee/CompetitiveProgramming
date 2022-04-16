#include <iostream>
#include <vector>
#include <functional>

typedef long long Long;

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    std::vector<std::vector<Long>> dp(n, std::vector<Long>(n*m+1, -1));

    std::function<Long(int, int)> countCases = [&](int start, int sum) -> Long {
        if (start == n) {
            return 1;
        }
        Long& result = dp[start][sum];
        if (result != -1) {
            return result;
        }

        result = 0;
        for (int v = 1; v <= m && v <= sum; ++v) {
            result += countCases(start+1, sum-v);
            result %= 998244353;
        }
        return result;
    };

    printf("%lld", countCases(0, k));
    
    return 0;
}