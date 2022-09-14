#include <iostream>
#include <algorithm>
#include <vector>

int n;
std::vector<int> in[501];
int dp[501], cost[501];

int getMinTime(int goal) {
    if (dp[goal] != -1) {
        return dp[goal];
    }

    int preparing = 0;
    for (int prev : in[goal]) {
        preparing = std::max(getMinTime(prev), preparing);
    }

    return dp[goal] = preparing + cost[goal];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    std::fill(dp, dp+n+1, -1);
    
    for (int i = 1; i <= n; ++i) {
        int prev;
        std::cin >> cost[i];
        while ((std::cin >> prev), prev != -1) {
            in[i].push_back(prev);
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d\n", getMinTime(i));
    }

    return 0;
}