#include <iostream>
#include <algorithm>

int n;
int table[3];
int maxDp[3];
int minDp[3];

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d", table, table+1, table+2);

        if (i == 0) {
            for (int j = 0; j < 3; ++j) {
                maxDp[j] = minDp[j] = table[j];
            }
        } else {
            int newMaxDp[3], newMinDp[3];
            for (int j = 0; j < 3; ++j) {
                int maxPrev = -1, minPrev = INT32_MAX;
                for (int p = std::max(j-1, 0); p <= std::min(2, j+1); ++p) {
                    maxPrev = std::max(maxPrev, maxDp[p]);
                    minPrev = std::min(minPrev, minDp[p]);
                }
                newMaxDp[j] = maxPrev + table[j];
                newMinDp[j] = minPrev + table[j];
            }
            std::copy(newMaxDp, newMaxDp+3, maxDp);
            std::copy(newMinDp, newMinDp+3, minDp);
        }
    }

    printf("%d %d", *std::max_element(maxDp, maxDp + 3), *std::min_element(minDp, minDp + 3));

    return 0;
}