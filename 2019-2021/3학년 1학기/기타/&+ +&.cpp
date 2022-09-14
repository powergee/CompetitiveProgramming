#include <iostream>
#include <algorithm>
#include <climits>

using Long = long long;
Long bits[2][30];
Long minPart[2][30][2];
Long maxPart[2][30][2];
Long min[2][30][2];
Long max[2][30][2];

int main() {
    std::fill(&minPart[0][0][0], &minPart[0][0][0]+sizeof(minPart)/sizeof(Long), INT64_MAX);
    std::fill(&maxPart[0][0][0], &maxPart[0][0][0]+sizeof(maxPart)/sizeof(Long), INT64_MIN);
    std::fill(&min[0][0][0], &min[0][0][0]+sizeof(min)/sizeof(Long), INT64_MAX);
    std::fill(&max[0][0][0], &max[0][0][0]+sizeof(max)/sizeof(Long), INT64_MIN);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            Long val;
            scanf("%lld", &val);

            for (int k = 0; k < 30; ++k) {
                if (val & (1<<k)) {
                    bits[i][k]++;
                }

                Long mask = (1<<(k+1))-1;
                Long part = val & mask;
                int msb = (val & (1<<k)) ? 1 : 0;
                if (part < minPart[i][k][msb]) {
                    minPart[i][k][msb] = part;
                    min[i][k][msb] = val;
                }
                if (maxPart[i][k][msb] < part) {
                    maxPart[i][k][msb] = part;
                    max[i][k][msb] = val;
                }
            }
        }
    }


    Long ans[2] = {0, INT64_MAX};
    for (int i = 0; i < 30; ++i) {
        ans[0] += (bits[0][i]%1999) * (bits[1][i]%1999) * ((1<<i)%1999);
        ans[0] %= 1999;
    }

    for (int i = 0; i < 30; ++i) {
        for (int m1 = 0; m1 < 2; ++m1) {
            for (int m2 = 0; m2 < 2; ++m2) {
                if (min[0][i][m1] == INT64_MAX || min[1][i][m2] == INT64_MAX ||
                    max[0][i][m1] == INT64_MIN || max[1][i][m2] == INT64_MIN) {
                    continue;
                }
                ans[1] &= min[0][i][m1]+min[1][i][m2];
                ans[1] &= min[0][i][m1]+max[1][i][m2];
                ans[1] &= max[0][i][m1]+min[1][i][m2];
                ans[1] &= max[0][i][m1]+max[1][i][m2];
            }
        }
    }

    printf("%lld %lld", ans[0], ans[1]);

    return 0;
}