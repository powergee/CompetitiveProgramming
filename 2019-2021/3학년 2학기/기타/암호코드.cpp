#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using Long = long long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;

    std::vector<Long> dp(str.size(), -1);

    std::function<Long(int)> countCases;
    countCases = [&](int start) -> Long {
        if (start == str.size()) {
            return 1;
        }
        if (dp[start] != -1) {
            return dp[start];
        }
        if (str[start] == '0') {
            return dp[start] = 0;
        }
        
        dp[start] = countCases(start+1);
        if (start+1 < str.size()) {
            int seg = (str[start]-'0')*10 + (str[start+1]-'0');
            if (0 < seg && seg <= 26) {
                dp[start] += countCases(start+2);
            }
        }
        dp[start] %= 1000000;

        return dp[start];
    };

    std::cout << countCases(0);
    return 0;
}