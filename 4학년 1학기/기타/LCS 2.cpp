#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum Decision { SkipA, SkipB, Match, None };
using DPState = std::pair<int, Decision>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string a, b;
    std::cin >> a >> b;

    std::vector<std::vector<DPState>> dp(a.size(), std::vector<DPState>(b.size(), std::make_pair(-1, None)));
    std::function<DPState(int, int)> findLCS = [&](int aStart, int bStart) -> DPState {
        if (a.size() <= aStart || b.size() <= bStart) {
            return {0, None};
        }

        auto& result = dp[aStart][bStart];
        if (result.first != -1) {
            return result;
        }

        { // SkipA
            auto sub = findLCS(aStart+1, bStart);
            sub.second = SkipA;
            result = std::max(result, sub);
        }
        { // SkipB
            auto sub = findLCS(aStart, bStart+1);
            sub.second = SkipB;
            result = std::max(result, sub);
        }
        if (a[aStart] == b[bStart]) { // Match
            auto sub = findLCS(aStart+1, bStart+1);
            sub.first++;
            sub.second = Match;
            result = std::max(result, sub);
        }

        return result;
    };

    auto found = findLCS(0, 0);
    std::cout << found.first << "\n";

    for (int i = 0, j = 0; i < a.size() && j < b.size();) {
        if (dp[i][j].second == Match) {
            std::cout << a[i];
        }
        if (dp[i][j].second == SkipA) {
            ++i;
        } else if (dp[i][j].second == SkipB) {
            ++j;
        } else {
            ++i, ++j;
        }
    }

    return 0;
}