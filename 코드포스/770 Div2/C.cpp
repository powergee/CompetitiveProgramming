#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        if (k == 1) {
            printf("YES\n");
            for (int i = 0; i < n; ++i) {
                printf("%d\n", i+1);
            }
        } else if (n%2 == 0) {
            printf("YES\n");
            for (int i = 0; i < n/2; ++i) {
                for (int j = 0; j < k; ++j) {
                    printf("%d ", 2*k*i+1 + 2*j);
                }
                printf("\n");
                for (int j = 0; j < k; ++j) {
                    printf("%d ", 2*k*i+2 + 2*j);
                }
                printf("\n");
            }
        } else {
            printf("NO\n");
        }
    }

    return 0;
}