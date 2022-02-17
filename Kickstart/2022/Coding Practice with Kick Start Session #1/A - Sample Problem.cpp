#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        int n, m;
        scanf("%d %d", &n, &m);

        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int candies;
            scanf("%d", &candies);
            sum += candies;
        }

        printf("Case #%d: %d\n", t, sum%m);
    }

    return 0;
}