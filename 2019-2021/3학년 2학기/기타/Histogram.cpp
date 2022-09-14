#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int b, n;
int nums[4001];
int sum[4001], sqSum[4001];
double dp[4001][31];

double getMinError(int last, int buck) {
    if (last == 0 || buck == 0) {
        return last == 0 && buck == 0 ? 0 : INT32_MAX;
    }

    double& result = dp[last][buck];
    if (result >= 0) {
        return result;
    }

    result = INT32_MAX;
    for (int i = buck; i <= last; ++i) {
        double currSqSum = sqSum[last] - sqSum[i-1];
        double currSum = sum[last] - sum[i-1];
        double mean = currSum / (last-i+1);
        double current = currSqSum - 2*mean*currSum + mean*mean*(last-i+1) + getMinError(i-1, buck-1);
        result = std::min(result, current);
    }
    return result;
}

int main() {
    scanf("%d%d", &b, &n);

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(double), -1.0);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", nums+i);
        sum[i] = sum[i-1] + nums[i];
        sqSum[i] = sqSum[i-1] + nums[i]*nums[i];
    }

    double answer = getMinError(n, b);
    for (int buck = 1; buck < b; ++buck) {
        answer = std::min(answer, getMinError(n, buck));
    }
    printf("%.9lf", answer);

    return 0;
}