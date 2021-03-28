#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        int n, c;
        scanf("%d %d", &n, &c);

        int costs[100] = {0, };
        if (n-1 <= c && c <= n*(n+1)/2-1) {
            int spare = c;
            for (int r = n-1; r >= 0 && spare; --r) {
                for (int i = 0; i <= r && spare; ++i) {
                    if (i == n-1) {
                        continue;
                    }
                    --spare;
                    ++costs[i];
                }
            }

            int result[100];
            for (int i = 0; i < n; ++i) {
                result[i] = i+1;
            }

            for (int i = n-2; i >= 0; --i) {
                int r = i + costs[i] - 1;
                std::reverse(result+i, result+r+1);
            }

            for (int i = 0; i < n; ++i) {
                printf("%d ", result[i]);
            }
            printf("\n");
        } else {
            printf("IMPOSSIBLE\n");
        }
    }
}