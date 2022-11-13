#include <iostream>
#include <vector>
#include <functional>

typedef long long Long;
const Long MOD = 1000000007;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }

        enum EdgeKind { Less, LessOrEqual };
        std::vector<std::vector<std::pair<int, EdgeKind>>> tree(n);
        std::function<int(int, int)> buildTree;
        buildTree = [&](int l, int r) -> int {
            int maxVal = INT32_MIN;
            std::vector<int> maxValPos;
            for (int i = l; i <= r; ++i) {
                if (maxVal < arr[i]) {
                    maxValPos.resize(0);
                    maxVal = arr[i];
                    maxValPos.push_back(i);
                } else if (maxVal == arr[i]) {
                    maxValPos.push_back(i);
                }
            }

            if (maxValPos.front() > l) {
                tree[maxValPos.front()].emplace_back(buildTree(l, maxValPos.front()-1), Less);
            }
            for (int i = 1; i < maxValPos.size(); ++i) {
                tree[maxValPos[i-1]].emplace_back(maxValPos[i], LessOrEqual);
                if (maxValPos[i]-maxValPos[i-1] >= 2) {
                    tree[maxValPos[i]].emplace_back(buildTree(maxValPos[i-1]+1, maxValPos[i]-1), Less);
                }
            }
            if (maxValPos.back() < r) {
                tree[maxValPos.back()].emplace_back(buildTree(maxValPos.back()+1, r), LessOrEqual);
            }
            return maxValPos.front();
        };

        int root = buildTree(0, n-1);

        std::vector<std::vector<Long>> dp(n, std::vector<Long>(m+1, -1));
        std::vector<std::vector<Long>> dpSum(n, std::vector<Long>(m+1, -1));

        std::function<Long(int, int)> countCases;
        std::function<Long(int, int)> countCasesSum;

        countCases = [&](int start, int val) -> Long {
            Long& result = dp[start][val];
            if (result != -1) {
                return result;
            } else if (val == 0) {
                return result = 0;
            }
            result = 1;
            for (auto [next, kind] : tree[start]) {
                result *= countCasesSum(next, val - (kind == Less ? 1 : 0));
                result %= MOD;
            }
            return result;
        };

        countCasesSum = [&](int start, int maxVal) -> Long {
            Long& result = dpSum[start][maxVal];
            if (result != -1) {
                return result;
            } else if (maxVal == 0) {
                return result = 0;
            }
            return result = (countCasesSum(start, maxVal-1) + countCases(start, maxVal)) % MOD;
        };

        std::cout << countCasesSum(root, m) << "\n";
    }

    return 0;
}