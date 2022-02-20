#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int acc = 0;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            acc |= val;
        }

        printf("%d\n", acc);
    }

    return 0;
}