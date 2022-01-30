#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        n--;

        int e = 1;
        while (e*2 <= n) {
            e *= 2;
        }
        for (int i = 1; i < e; ++i) {
            printf("%d ", i);
        }
        printf("%d %d ", 0, e);
        for (int i = e+1; i <= n; ++i) {
            printf("%d ", i);
        }
        printf("\n");
    }

    return 0;
}