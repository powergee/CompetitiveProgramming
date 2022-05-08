#include <iostream>
#include <string>
#include <vector>
#include <functional>
#define operations first
#define segments second

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        std::string str;
        std::cin >> str;

        auto getCost = [&](int index, int goal) {
            char gCh = '0' + goal;
            return (str[index*2] != gCh ? 1 : 0) + (str[index*2+1] != gCh ? 1 : 0);
        };

        std::pair<int, int> dp[n/2][2];
        dp[0][0] = std::make_pair(getCost(0, 0), 1);
        dp[0][1] = std::make_pair(getCost(0, 1), 1);
        for (int i = 1; i < n/2; ++i) {
            for (int currColor = 0; currColor < 2; ++currColor) {
                dp[i][currColor] = { INT32_MAX/2, INT32_MAX/2 };

                std::pair<int, int> same = dp[i-1][currColor];
                same.first += getCost(i, currColor);
                dp[i][currColor] = std::min(dp[i][currColor], same);

                int oppoColor = currColor ? 0 : 1;
                std::pair<int, int> diff = dp[i-1][oppoColor];
                diff.first += getCost(i, currColor);
                diff.second += 1;
                dp[i][currColor] = std::min(dp[i][currColor], diff);
            }
        }

        auto answer = std::min(dp[n/2-1][0], dp[n/2-1][1]);
        std::cout << answer.first << " " << answer.second << "\n";
    }

    return 0;
}