#include <iostream>
#include <algorithm>

int dp[1001];

bool canWin(int stones) {
    if (stones == 1 || stones == 3 || stones == 4) {
        return true;
    }

    if (dp[stones] != -1) {
        return dp[stones] == 1;
    }

    bool result = false;
    if (stones > 1 && !canWin(stones-1)) {
        result = true;
    }
    if (stones > 3 && !canWin(stones-3)) {
        result = true;
    }
    if (stones > 4 && !canWin(stones-4)) {
        result = true;
    }

    dp[stones] = result ? 1 : 0;
    return result;
}

int main() {
    std::fill(dp, dp+1001, -1);
    int n;
    scanf("%d", &n);
    if (canWin(n)) {
        printf("SK");
    } else {
        printf("CY");
    }

    return 0;
}