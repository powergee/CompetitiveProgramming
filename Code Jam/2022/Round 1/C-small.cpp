#include <iostream>
#include <string>
#include <numeric>
#include <vector>
#include <functional>
#include <algorithm>
#define MAX 1000000000LL

typedef long long Long;

void solve() {
    int e, w;
    std::cin >> e >> w;

    std::vector<std::vector<std::string>> states(e);
    int maxStateCount = 0;
    for (int i = 0; i < e; ++i) {
        std::vector<int> count(w);
        std::string comb;
        for (int j = 0; j < w; ++j) {
            int weight;
            std::cin >> weight;
            count[weight]++;
            for (int k = 0; k < weight; ++k) {
                comb += std::to_string(j);
            }
        }

        do {
            states[i].push_back(comb);
        } while (std::next_permutation(comb.begin(), comb.end()));
        maxStateCount = std::max(maxStateCount, (int)states[i].size());
    }

    std::vector<std::vector<int>> dp(e, std::vector<int>(maxStateCount, -1));

    std::function<int(int, int)> findMinCount = [&](int exIdx, int stIdx) -> int {
        int& result = dp[exIdx][stIdx];
        if (result != -1) {
            return result;
        }
        if (exIdx == e-1) {
            return result = states[exIdx][stIdx].size();
        }

        result = INT32_MAX;
        int i = stIdx;
        for (int j = 0; j < states[exIdx+1].size(); ++j) {
            int cpre = 0;
            int size = std::min(states[exIdx][i].size(), states[exIdx+1][j].size());
            for (cpre = 0; cpre < size; ++cpre) {
                if (states[exIdx][i][cpre] != states[exIdx+1][j][cpre]) {
                    break;
                }
            }

            result = std::min(result,
                int(states[exIdx][i].size()+states[exIdx+1][j].size())-2*cpre + findMinCount(exIdx+1, j));
        }

        return result;
    };

    std::vector<int> cands;
    for (int i = 0; i < states[0].size(); ++i) {
        cands.push_back(states[0][i].size() + findMinCount(0, i));
    }
    std::cout << *std::min_element(cands.begin(), cands.end()) << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}