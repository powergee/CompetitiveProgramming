#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum ReduceKind { S, T, Both, None };
using LCSBucket = std::pair<int, ReduceKind>;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;
    int n = s.size();
    int m = t.size();

    std::vector<std::vector<LCSBucket>> dp(s.size(), std::vector<LCSBucket>(t.size(), {-1, None}));

    std::function<LCSBucket(int, int)> findLCS = [&](int sIdx, int tIdx) -> LCSBucket {
        if (sIdx == -1 || tIdx == -1) {
            return {0, None};
        }

        LCSBucket& result = dp[sIdx][tIdx];
        if (result.first != -1) {
            return result;
        }

        result = std::max(
            LCSBucket(findLCS(sIdx-1, tIdx).first, S),
            LCSBucket(findLCS(sIdx, tIdx-1).first, T)
        );
        if (s[sIdx] == t[tIdx]) {
            result = std::max(result, {findLCS(sIdx-1, tIdx-1).first+1, Both});
        }
        return result;
    };
    findLCS(n-1, m-1);

    auto transfer = [&](int& sIdx, int& tIdx) -> void {
        switch (dp[sIdx][tIdx].second)
        {
        case S:
            --sIdx;
            break;
        case T:
            --tIdx;
            break;
        case Both:
            --sIdx; --tIdx;
            break;
        default:
            sIdx = tIdx = -1;
            break;
        }
    };

    std::vector<char> stack;
    for (int i = n-1, j = m-1; i != -1; transfer(i, j)) {
        if (dp[i][j].second == Both) {
            stack.push_back(s[i]);
        }
    }

    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        std::cout << *it;
    }
    
    return 0;
}