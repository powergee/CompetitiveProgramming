#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>

using Long = long long;
using BigInt = __int128_t;

std::string toString(BigInt bi) {
    std::string result;
    while (bi) {
        int digit = bi % 10;
        result += char('0' + digit);
        bi /= 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Long n, x;
    std::cin >> n >> x;
    
    std::map<BigInt, int> dp;
    std::function<int(BigInt)> getMinAnswer = [&](BigInt x) -> int {
        if (dp.count(x)) {
            return dp[x];
        }
        
        std::string xStr = toString(x);
        if (xStr.size() == n) {
            return dp[x] = 0;
        }

        dp[x] = INT32_MAX/2;
        for (char ch : xStr) {
            if (ch <= '1') {
                continue;
            }
            dp[x] = std::min(dp[x], getMinAnswer(x*(ch-'0'))+1);
        }
        return dp[x];
    };
    int answer = getMinAnswer(x);
    std::cout << (answer == INT32_MAX/2 ? -1 : answer);

    return 0;
}