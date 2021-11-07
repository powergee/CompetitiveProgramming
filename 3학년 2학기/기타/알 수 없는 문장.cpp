#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#define UNDEFINED -1
#define IMPOSSIBLE 1000

int main() {
    std::string target;
    int n, tSize;

    std::cin >> target;
    tSize = target.size();

    std::cin >> n;
    std::string words[n];
    
    for (int i = 0; i < n; ++i) {
        std::cin >> words[i];
    }

    std::vector<int> dp(tSize+1, UNDEFINED);
    std::function<int(int)> getMinCost;
    getMinCost = [&](int start) -> int {
        if (dp[start] != UNDEFINED) {
            return dp[start];
        }
        if (start == tSize) {
            return dp[start] = 0;
        }

        dp[start] = IMPOSSIBLE;
        for (int i = 0; i < n; ++i) {
            if (words[i].size() <= tSize-start) {
                std::map<char, int> tCnt, wCnt;
                int cost = 0;
                for (int j = 0; j < words[i].size(); ++j) {
                    cost += (target[start+j] == words[i][j] ? 0 : 1);
                    tCnt[target[start+j]]++;
                    wCnt[words[i][j]]++;
                }

                if (tCnt == wCnt) {
                    dp[start] = std::min(dp[start], cost + getMinCost(start+words[i].size()));
                }
            }
        }

        return dp[start];
    };

    int answer = getMinCost(0);
    if (answer == IMPOSSIBLE) {
        std::cout << "-1";
    } else {
        std::cout << answer;
    }

    return 0;
}
