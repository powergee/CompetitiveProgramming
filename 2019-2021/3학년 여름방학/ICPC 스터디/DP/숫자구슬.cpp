#include <iostream>
#include <algorithm>

int n, m;
int arr[300];
int sum[300][300];
int dp[301][300];
int width[301][300];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        std::fill(dp[i], dp[i]+m+1, INT32_MAX);
    }

    for (int i = 0; i < n; ++i) {
        sum[i][i] = arr[i];
        for (int j = i+1; j < n; ++j) {
            sum[i][j] = sum[i][j-1] + arr[j];
        }
    }

    for (int s = 0; s < n; ++s) {
        dp[1][s] = sum[s][n-1];
        width[1][s] = n-s;
    }

    for (int g = 2; g <= m; ++g) {
        for (int s = 0; s < n-g+1; ++s) {
            dp[g][s] = std::max(sum[s][s], dp[g-1][s+1]);
            width[g][s] = 1;
            for (int i = s+1; i < n-g+1; ++i) {
                int cand = std::max(sum[s][i], dp[g-1][i+1]);
                if (cand < dp[g][s]) {
                    dp[g][s] = cand;
                    width[g][s] = i-s+1;
                }
            }
        }
    }

    printf("%d\n", dp[m][0]);

    int group = m;
    for (int i = 0; i < n; i += width[m--][i]) {
        printf("%d ", width[m][i]);
    }

    return 0;
}