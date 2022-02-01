#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::pair<int, int>> matrices(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &matrices[i].first, &matrices[i].second);
    }
    
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
    std::function<int(int, int)> getMinCost = [&](int left, int right) -> int {
        int& result = dp[left][right];
        if (result != -1) {
            return result;
        } else if (left == right) {
            return 0;
        }

        result = INT32_MAX;
        for (int mid = left; mid < right; ++mid) {
            int curr = getMinCost(left, mid) + getMinCost(mid+1, right);
            curr += matrices[left].first * matrices[mid].second * matrices[right].second;
            result = std::min(result, curr);
        }
        return result;
    };

    printf("%d", getMinCost(0, n-1));

    return 0;
}