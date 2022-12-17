#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int dp[30][101][101][101];

int getBestDiff(int stage, int a, int b, int c) {
    int& result = dp[stage][a][b][c];
    if (result != INT32_MIN) {
        return result;
    }

    if (a > 0) {
        int earn = std::min(a, stage);
        result = std::max(result, earn - getBestDiff(stage+1, a-earn, b, c));
    }
    if (b > 0) {
        int earn = std::min(b, stage);
        result = std::max(result, earn - getBestDiff(stage+1, a, b-earn, c));
    }
    if (c > 0) {
        int earn = std::min(c, stage);
        result = std::max(result, earn - getBestDiff(stage+1, a, b, c-earn));
    }
    
    if (result == INT32_MIN) {
        result = 0;
    }
    return result;
}

int main() {
    std::fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(int), INT32_MIN);
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int a, b, c;
    std::cin >> a >> b >> c;
    
    int diff = getBestDiff(1, a, b, c);
    if (diff > 0) {
        std::cout << "F";
    } else if (diff < 0) {
        std::cout << "S";
    } else {
        std::cout << "D";
    }

    return 0;
}