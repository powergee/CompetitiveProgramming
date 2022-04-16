#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        
        if (n < 4) {
            printf("-1\n");
            continue;
        }

        for (int i = n; i >= 1; --i) {
            if (i % 2 == 1) {
                printf("%d ", i);
            }
        }
        printf("%d %d ", 4, 2);
        for (int i = 6; i <= n; ++i) {
            if (i % 2 == 0) {
                printf("%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}