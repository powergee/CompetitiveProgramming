#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int sum = -n;

        for (int i = 0; i < n; ++i) {
            int b;
            scanf("%d", &b);
            sum += b;
        }

        if (sum >= 0) {
            printf("%d\n", sum);
        } else {
            printf("%d\n", 1);
        }
    }

    return 0;
}