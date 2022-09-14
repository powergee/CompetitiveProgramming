#include <iostream>
#include <algorithm>

int n;
int dp[31][31][31];

int countCases(int r1, int r2, int r3) {
    if (r1 == n && r2 == n && r3 == n) {
        return 1;
    }

    int& result = dp[r1][r2][r3];
    if (result != -1) {
        return result;
    }

    result = 0;
    if (r1 <= r2 && r1 <= r3) {
        if (r1 == r2 && r1 < n) {
            result += countCases(r1+1, r2+1, r3);
        }
        if (r1 < n-1) {
            result += countCases(r1+2, r2, r3);
        }
    } else if (r2 <= r1 && r2 <= r3) {
        if (r2 == r3 && r2 < n) {
            result += countCases(r1, r2+1, r3+1);
        }
        if (r2 < n-1) {
            result += countCases(r1, r2+2, r3);
        }
    } else if (r3 < n-1) {
        result += countCases(r1, r2, r3+2);
    }

    return result;
}

int main() {
    std::fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(int), -1);
    scanf("%d", &n);
    printf("%d", countCases(0, 0, 0));

    return 0;
}