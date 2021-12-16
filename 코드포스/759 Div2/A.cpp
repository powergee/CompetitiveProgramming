#include <cstdio>
#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int history[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", history+i);
        }

        int prev = history[0];
        int height = (prev ? 2 : 1);
        for (int i = 1; i < n; ++i) {
            if (history[i]) {
                if (prev) {
                    height += 5;
                } else {
                    height += 1;
                }
            } else {
                if (!prev) {
                    height = -1;
                    break;
                }
            }
            prev = history[i];
        }

        printf("%d\n", height);
    }

    return 0;
}
