#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        if (n == 4 && k == 3) {
            printf("-1\n");
        } else if (k == 0) {
            for (int i = 0; i < n/2; ++i) {
                printf("%d %d\n", i, n-1-i);
            }
        } else if (k == n-1) {
            printf("%d %d\n", 0, 1);
            printf("%d %d\n", n/2-1, n-1);
            printf("%d %d\n", n/2, n-2);
            for (int i = 2; i < n/2-1; ++i) {
                printf("%d %d\n", i, n-1-i);
            }
        } else {
            int kPair = n-1-k;
            printf("%d %d\n", k, n-1);
            printf("%d %d\n", kPair, 0);
            for (int i = 1; i < std::min(k, kPair); ++i) {
                printf("%d %d\n", i, n-1-i);
            }
            for (int i = std::min(k, kPair)+1; i < n/2; ++i) {
                printf("%d %d\n", i, n-1-i);
            }
        }
    }

    return 0;
}