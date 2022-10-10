#include <iostream>
#include <vector>
#include <algorithm>

int cost[12][12];
int dp[1<<6][6][2];

int getMinCost(int mask, int group, int side) {
    int& result = dp[mask][group][side];
    if (result != -1) {
        return result;
    }

    int curr = group*2+side;
    int oppo = group*2+(side ? 0 : 1);
    result = INT32_MAX;
    for (int nextGroup = 0; nextGroup < 6; ++nextGroup) {
        if (mask&(1<<nextGroup) || group == nextGroup) {
            continue;
        }
        int l = nextGroup*2;
        int r = nextGroup*2+1;
        result = std::min(result, cost[curr][oppo] + cost[oppo][l] + getMinCost(mask|(1<<group), nextGroup, 0));
        result = std::min(result, cost[curr][oppo] + cost[oppo][r] + getMinCost(mask|(1<<group), nextGroup, 1));
    }
    if (result == INT32_MAX) {
        result = cost[curr][oppo];
    }
    return result;
}

int main() {
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            std::cin >> cost[i][j];
        }
    }

    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(int), -1);
    int answer = INT32_MAX;
    for (int group = 0; group < 6; ++group) {
        answer = std::min(answer, getMinCost(0, group, 0));
        answer = std::min(answer, getMinCost(0, group, 1));
    }

    std::cout << answer;

    return 0;
}