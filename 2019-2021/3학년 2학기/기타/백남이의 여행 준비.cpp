#include <iostream>
#include <vector>
#include <algorithm>

int n, m;
std::pair<int, short> items[100];
int bag[100];
int dp[100][1000001];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%d %hd", &items[i].first, &items[i].second);
    }
    int maxBag = -1;
    for (int i = 0; i < m; ++i) {
        scanf("%d", bag+i);
        maxBag = std::max(maxBag, bag[i]);
    }

    for (int cap = 0; cap <= maxBag; ++cap) {
        dp[0][cap] = (items[0].first <= cap ? items[0].second : 0);
        for (int it = 1; it < n; ++it) {
            dp[it][cap] = dp[it-1][cap];
            if (items[it].first <= cap) {
                dp[it][cap] = std::max(dp[it][cap], items[it].second + dp[it-1][cap-items[it].first]);
            }
        }
    }

    int maxRatioIdx = -1;
    double maxRatio = -1;
    for (int i = 0; i < m; ++i) {
        double ratio = double(dp[n-1][bag[i]]) / bag[i];
        if (maxRatio < ratio) {
            maxRatio = ratio;
            maxRatioIdx = i;
        }
    }

    printf("%d", maxRatioIdx+1);

    return 0;
}