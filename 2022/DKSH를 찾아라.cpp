#include <iostream>
#include <vector>
#include <string>
#include <functional>

typedef long long Long;

int main() {
    int n;
    std::string str;
    std::cin >> n >> str;

    const char* ORDER = "DKSH";
    std::vector<std::vector<Long>> dp(n+1, std::vector<Long>(5, -1));
    std::function<Long(int, int)> countCases = [&](int start, int accepted) -> Long {
        if (dp[start][accepted] != -1) {
            return dp[start][accepted];
        }

        Long& result = dp[start][accepted];
        if (accepted == 4) {
            return result = 1;
        } else if (start == n) {
            return result = 0;
        }
        result = countCases(start+1, accepted);
        if (ORDER[accepted] == str[start]) {
            result += countCases(start+1, accepted+1);
        }
        return result;
    };

    std::cout << countCases(0, 0);

    return 0;
}