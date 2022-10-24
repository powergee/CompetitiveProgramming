#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int odd = 0;
        for (int i = 0; i < 2*n; ++i) {
            int v;
            scanf("%d", &v);
            if (v % 2) {
                ++odd;
            }
        }

        if (odd == n) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}