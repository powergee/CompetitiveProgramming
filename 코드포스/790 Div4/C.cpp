#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        char str[n][m+1];
        for (int i = 0; i < n; ++i) {
            scanf("%s", str[i]);
        }

        int answer = INT32_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                int diff = 0;
                for (int k = 0; k < m; ++k) {
                    diff += std::abs(str[i][k]-str[j][k]);
                }
                answer = std::min(answer, diff);
            }
        }
        printf("%d\n", answer);
    }

    return 0;
}