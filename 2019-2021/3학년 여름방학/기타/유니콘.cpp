#include <iostream>
#include <algorithm>
#include <cstring>
#define MOD 1000000007

typedef long long Long;

int n, m, l;
int pathLength;
char path[51];
char map[300][301];
Long casesDP[300][300][50];
Long sumDP[50];
Long horDP[300][50];
Long verDP[300][50];

Long countCases(int row, int col, int pathIdx);
Long getSum(int pathIdx);
Long getHorizontalSum(int row, int pathIdx);
Long getVerticalSum(int col, int pathIdx);

Long getMod(Long val, Long mod) {
    if (val >= 0) {
        return val % mod;
    }
    return getMod(val+mod, mod);
}

Long countCases(int row, int col, int pathIdx) {
    if (row < 0 || n <= row || col < 0 || m <= col) {
        return 0;
    }

    Long& result = casesDP[row][col][pathIdx];
    if (result != -1) {
        return result;
    }

    if (map[row][col] == path[pathIdx]) {
        if (pathIdx == pathLength-1) {
            return result = 1;
        }

        result = getSum(pathIdx+1);
        for (int r = row-1; r <= row+1; ++r) {
            result -= getHorizontalSum(r, pathIdx+1);
        }
        for (int c = col-1; c <= col+1; ++c) {
            result -= getVerticalSum(c, pathIdx+1);
        }

        for (int r = row-1; r <= row+1; ++r) {
            for (int c = col-1; c <= col+1; ++c) {
                result += countCases(r, c, pathIdx+1);
            }
        }
        result -= countCases(row-2, col-2, pathIdx+1);
        result -= countCases(row-2, col+2, pathIdx+1);
        result -= countCases(row+2, col-2, pathIdx+1);
        result -= countCases(row+2, col+2, pathIdx+1);
        result = getMod(result, MOD);
        return result;
    } else {
        return result = 0;
    }
}

Long getSum(int pathIdx) {
    Long& result = sumDP[pathIdx];
    if (result != -1) {
        return result;
    }

    result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result += countCases(i, j, pathIdx);
            result %= MOD;
        }
    }
    return result;
}

Long getHorizontalSum(int row, int pathIdx) {
    if (row < 0 || n <= row) {
        return 0;
    }

    Long& result = horDP[row][pathIdx];
    if (result != -1) {
        return result;
    }

    result = 0;
    for (int col = 0; col < m; ++col) {
        result += countCases(row, col, pathIdx);
        result %= MOD;
    }
    return result;
}

Long getVerticalSum(int col, int pathIdx) {
    if (col < 0 || m <= col) {
        return 0;
    }

    Long& result = verDP[col][pathIdx];
    if (result != -1) {
        return result;
    }

    result = 0;
    for (int row = 0; row < n; ++row) {
        result += countCases(row, col, pathIdx);
        result %= MOD;
    }
    return result;
}

int main() {
    scanf("%d %d %d", &n, &m, &l);
    scanf("%s", path);
    pathLength = strlen(path);
    for (int i = 0; i < n; ++i) {
        scanf("%s", map[i]);
    }

    std::fill(&sumDP[0], &sumDP[0] + sizeof(sumDP) / sizeof(Long), -1LL);
    std::fill(&horDP[0][0], &horDP[0][0] + sizeof(horDP) / sizeof(Long), -1LL);
    std::fill(&verDP[0][0], &verDP[0][0] + sizeof(verDP) / sizeof(Long), -1LL);
    std::fill(&casesDP[0][0][0], &casesDP[0][0][0] + sizeof(casesDP) / sizeof(Long), -1LL);

    printf("%lld", getSum(0));

    return 0;
}