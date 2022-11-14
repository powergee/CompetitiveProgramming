#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <limits>

typedef long long Long;

std::pair<Long, Long> toPoint(int row, int col) {
    int initX[] = { 2, 3, 5 };
    int initY[] = { 2, 6, 10 };
    int x = initX[row] + col*4;
    int y = initY[row];
    return { x, y };
}

const std::pair<Long, Long> POINT[26] = {
    ['Q'-'A'] = toPoint(0, 0),
    ['W'-'A'] = toPoint(0, 1),
    ['E'-'A'] = toPoint(0, 2),
    ['R'-'A'] = toPoint(0, 3),
    ['T'-'A'] = toPoint(0, 4),
    ['Y'-'A'] = toPoint(0, 5),
    ['U'-'A'] = toPoint(0, 6),
    ['I'-'A'] = toPoint(0, 7),
    ['O'-'A'] = toPoint(0, 8),
    ['P'-'A'] = toPoint(0, 9),

    ['A'-'A'] = toPoint(1, 0),
    ['S'-'A'] = toPoint(1, 1),
    ['D'-'A'] = toPoint(1, 2),
    ['F'-'A'] = toPoint(1, 3),
    ['G'-'A'] = toPoint(1, 4),
    ['H'-'A'] = toPoint(1, 5),
    ['J'-'A'] = toPoint(1, 6),
    ['K'-'A'] = toPoint(1, 7),
    ['L'-'A'] = toPoint(1, 8),

    ['Z'-'A'] = toPoint(2, 0),
    ['X'-'A'] = toPoint(2, 1),
    ['C'-'A'] = toPoint(2, 2),
    ['V'-'A'] = toPoint(2, 3),
    ['B'-'A'] = toPoint(2, 4),
    ['N'-'A'] = toPoint(2, 5),
    ['M'-'A'] = toPoint(2, 6),
};

Long getDist(char c1, char c2) {
    auto [x1, y1] = POINT[c1-'A'];
    auto [x2, y2] = POINT[c2-'A'];
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

Long dp[501][501];

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::string> cands(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cands[i];
    }
    std::string target;
    std::cin >> target;

    std::vector<std::string> minCand;
    Long minPenalty = std::numeric_limits<Long>::max();
    for (int i = 0; i < n; ++i) {
        std::string& cand = cands[i];
        for (int ci = 0; ci <= cand.size(); ++ci) {
            dp[ci][target.size()] = 1600 * (cand.size() - ci);
        }
        for (int ti = 0; ti <= target.size(); ++ti) {
            dp[cand.size()][ti] = 1600 * (target.size() - ti);
        }
        for (int ci = cand.size()-1; ci >= 0; --ci) {
            for (int ti = target.size()-1; ti >= 0; --ti) {
                dp[ci][ti] = std::min(
                    1600 + dp[ci][ti+1],
                    1600 + dp[ci+1][ti]
                );
                dp[ci][ti] = std::min(
                    getDist(cand[ci], target[ti]) + dp[ci+1][ti+1],
                    dp[ci][ti]
                );
            }
        }

        Long penalty = dp[0][0];
        if (penalty < minPenalty) {
            minPenalty = penalty;
            minCand = { cand };
        } else if (penalty == minPenalty) {
            minCand.push_back(cand);
        }
    }

    std::sort(minCand.begin(), minCand.end());
    for (auto s : minCand) {
        std::cout << s << " ";
    }

    return 0;
}