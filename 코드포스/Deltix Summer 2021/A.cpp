#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);

        if (a == 0 && b == 0) {
            printf("0\n");
        } else if (a == b) {
            printf("1\n");
        } else if ((a+b) % 2 == 0) {
            printf("2\n");
        } else {
            printf("-1\n");
        }
    }

    return 0;
}