#include <iostream>
#define INF (INT32_MAX/2)

int m, n, l, g;
int dp[100][100][201][2];

struct Junction {
    int right, down;
} junc[100][100];

int getMinGasUsage(int r, int c, int rotationRemain, int headingRight) {
    int& result = dp[r][c][rotationRemain][headingRight];
    if (result != -1) {
        return result;
    }
    if (r == m-1 && c == n-1) {
        return result = (rotationRemain == 0 ? 0 : INF);
    }

    result = INF;
    if (c+1 < n) {
        int nextRotRem = rotationRemain - (headingRight ? 0 : 1);
        if (nextRotRem >= 0) {
            int gas = junc[r][c].right + getMinGasUsage(r, c+1, nextRotRem, 1);
            result = std::min(result, gas);
        }
    }
    if (r+1 < m) {
        int nextRotRem = rotationRemain - (headingRight ? 1 : 0);
        if (nextRotRem >= 0) {
            int gas = junc[r][c].down + getMinGasUsage(r+1, c, nextRotRem, 0);
            result = std::min(result, gas);
        }
    }

    return result;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d %d %d %d", &m, &n, &l, &g);

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n-1; ++c) {
                scanf("%d", &junc[r][c].right);
            }
        }
        for (int r = 0; r < m-1; ++r) {
            for (int c = 0; c < n; ++c) {
                scanf("%d", &junc[r][c].down);
            }
        }

        int maxRotation = 2*std::min(n, m);
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                for (int rot = 0; rot <= maxRotation; ++rot) {
                    dp[r][c][rot][0] = dp[r][c][rot][1] = -1;
                }
            }
        }

        bool printed = false;
        for (int rot = 1; rot <= maxRotation; ++rot) {
            int gas = std::min(getMinGasUsage(0, 0, rot, 0), getMinGasUsage(0, 0, rot, 1));
            if (gas <= g) {
                printed = true;
                printf("%d\n", l*(n+m-2)+rot);
                break;
            }
        }

        if (!printed) {
            printf("-1\n");
        }
    }

    return 0;
}