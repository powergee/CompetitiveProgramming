#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int LCS(std::string& str, std::string& sub)
{
    std::vector<std::vector<int>> dp;
    dp.resize(sub.size() + 1);
    dp[0].resize(str.size() + 1);
    std::fill(dp[0].begin(), dp[0].end(), 0);

    for (int row = 1; row < (int)dp.size(); ++row)
    {
        dp[row].push_back(0);
        for (int col = 1; col <= (int)str.size(); ++col)
        {
            if (sub[row - 1] == str[col - 1])
                dp[row].push_back(dp[row - 1][col - 1] + 1);
            else
                dp[row].push_back(std::max(dp[row - 1][col], dp[row][col - 1]));
        }
    }

    return dp.back().back();
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string a, b;
    std::cin >> a >> b;

    std::cout << LCS(a, b);

    return 0;
}