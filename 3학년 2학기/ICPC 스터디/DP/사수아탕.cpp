#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

enum Selection { Positive = 0, Negative = 1 };

int n, m;
std::vector<int> pos, neg;
int dp[301][301][301][2];

int getMinLoss(int posIdx, int negIdx, int totalRemain, Selection prev) {
    int& result = dp[posIdx][negIdx][totalRemain][prev];
    if (result != -1) {
        return result;
    }

    if (totalRemain == 0) {
        return result = 0;
    }

    int currX;
    if (posIdx == 0 && negIdx == 0) {
        currX = 0;
    } else {
        currX = (prev == Positive ? pos[posIdx-1] : neg[negIdx-1]);
    }

    result = INT32_MAX;
    if (posIdx < pos.size()) {
        result = std::min(result, (pos[posIdx]-currX)*totalRemain + getMinLoss(posIdx+1, negIdx, totalRemain-1, Positive));
    }
    if (negIdx < neg.size()) {
        result = std::min(result, (currX-neg[negIdx])*totalRemain + getMinLoss(posIdx, negIdx+1, totalRemain-1, Negative));
    }

    return result;
}

int main() {
    std::fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(int), -1);
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        (x >= 0 ? pos : neg).push_back(x);
    }

    std::sort(pos.begin(), pos.end(), std::less<int>());
    std::sort(neg.begin(), neg.end(), std::greater<int>());
    
    int maxCandies = 0;
    for (int totalRemain = 1; totalRemain <= n; ++totalRemain) {
        maxCandies = std::max(maxCandies, totalRemain*m - getMinLoss(0, 0, totalRemain, Positive));
    }

    printf("%d", maxCandies);

    return 0;
}