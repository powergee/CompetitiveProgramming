#include <iostream>
#include <vector>
#include <algorithm>

int n, k;
std::pair<int, int> items[100];
int dp[100001][100];

int main() {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &items[i].first, &items[i].second);
    }

    for (int cap = 0; cap <= k; ++cap) {
        dp[cap][0] = (items[0].first <= cap ? items[0].second : 0);
        for (int it = 1; it < n; ++it) {
            dp[cap][it] = dp[cap][it-1];
            if (items[it].first <= cap) {
                dp[cap][it] = std::max(dp[cap][it], items[it].second + dp[cap-items[it].first][it-1]);
            }
        }
    }
    printf("%d", dp[k][n-1]);
    return 0;
}