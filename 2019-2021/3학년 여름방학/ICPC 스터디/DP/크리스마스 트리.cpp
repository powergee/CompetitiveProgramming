#include <iostream>
#include <algorithm>

typedef long long Long;

int n;
Long combDP[11][11];
Long dp[11][101][101][101];

Long calcComb(int n, int m) {
    if (n < m) {
        return 0;
    } else if (n == 0 || m == 0) {
        return 1;
    } else if (combDP[n][m] != -1) {
        return combDP[n][m];
    } else {
        return combDP[n][m] = calcComb(n-1, m-1) + calcComb(n-1, m);
    }
}

Long countCases(int level, int red, int green, int blue) {
    if (n+1 == level) {
        return 1;
    }

    Long& result = dp[level][red][green][blue];
    if (result != -1) {
        return result;
    }

    result = 0;
    if (level <= red) {
        result += countCases(level+1, red-level, green, blue);
    }
    if (level <= green) {
        result += countCases(level+1, red, green-level, blue);
    }
    if (level <= blue) {
        result += countCases(level+1, red, green, blue-level);
    }

    if (level % 2 == 0) {
        if (level/2 <= red && level/2 <= green) {
            result += calcComb(level, level/2) * countCases(level+1, red-level/2, green-level/2, blue);
        }
        if (level/2 <= green && level/2 <= blue) {
            result += calcComb(level, level/2) * countCases(level+1, red, green-level/2, blue-level/2);
        }
        if (level/2 <= red && level/2 <= blue) {
            result += calcComb(level, level/2) * countCases(level+1, red-level/2, green, blue-level/2);
        }
    }

    if (level % 3 == 0 && level/3 <= red && level/3 <= green && level/3 <= blue) {
        result += calcComb(level, level/3) * calcComb(level/3*2, level/3) * countCases(level+1, red-level/3, green-level/3, blue-level/3);
    }

    return result;
}

int main() {
    int red, green, blue;
    scanf("%d %d %d %d", &n, &red, &green, &blue);
    std::fill(&combDP[0][0], &combDP[0][0]+sizeof(combDP)/sizeof(Long), -1LL);
    std::fill(&dp[0][0][0][0], &dp[0][0][0][0]+sizeof(dp)/sizeof(Long), -1LL);
    printf("%lld", countCases(1, red, green, blue));

    return 0;
}