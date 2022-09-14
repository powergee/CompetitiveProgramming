#include <iostream>
#include <algorithm>

int T, k;
int p[100], n[100];
int dp[10001][100];

int countCases(int goal, int index) {
    if (index == k) {
        return goal == 0 ? 1 : 0;
    }

    int& result = dp[goal][index];
    if (result != -1) {
        return result;
    }

    result = 0;
    for (int use = 0; use <= n[index]; ++use) {
        if (goal < p[index]*use) {
            break;
        }
        result += countCases(goal - p[index]*use, index+1);
    }
    
    return result;
}

int main() {
    scanf("%d%d", &T, &k);

    for (int i = 0; i < k; ++i) {
        scanf("%d %d", p+i, n+i);
    }

    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), -1);
    printf("%d", countCases(T, 0));

    return 0;
}