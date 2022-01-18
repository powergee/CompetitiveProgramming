#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <algorithm>

using Segment = std::tuple<int, int, int>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;

        std::map<std::string, Segment> segs;
        for (int i = 0; i < n; ++i) {
            std::string known;
            std::cin >> known;
            for (int j = 0; j < m-1; ++j) {
                segs[known.substr(j, 2)] = std::make_tuple(j+1, j+2, i+1);
            }
            for (int j = 0; j < m-2; ++j) {
                segs[known.substr(j, 3)] = std::make_tuple(j+1, j+3, i+1);
            }
        }

        std::string input;
        std::cin >> input;
        std::vector<int> dp(m+1, -1);

        std::function<int(int)> findAnswer;
        findAnswer = [&](int start) -> int {
            if (m == start) {
                return dp[start] = 1;
            }

            if (dp[start] != -1) {
                return dp[start];
            }

            std::string token = input.substr(start, 3);
            if (start+2 < m && segs.find(token) != segs.end()) {
                if (findAnswer(start+3) != -2) {
                    return dp[start] = 3;
                }
            }
            token = input.substr(start, 2);
            if (start+1 < m && segs.find(token) != segs.end()) {
                if (findAnswer(start+2) != -2) {
                    return dp[start] = 2;
                }
            }
            
            return dp[start] = -2;
        };

        if (findAnswer(0) != -2) {
            std::vector<Segment> answer;
            for (int i = 0; dp[i] != 1; i += dp[i]) {
                answer.push_back(segs[input.substr(i, dp[i])]);
            }
            std::cout << answer.size() << "\n";
            for (auto [l, r, i] : answer) {
                std::cout << l << " " << r << " " << i << "\n";
            }
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}