#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        if (n % 3 == 0) {
            while (n > 0) {
                printf("21");
                n -= 3;
            }
            printf("\n");
        } else if (n % 3 == 1) {
            printf("1");
            n--;
            while (n > 0) {
                printf("21");
                n -= 3;
            }
            printf("\n");
        } else {
            printf("2");
            n -= 2;
            while (n > 0) {
                printf("12");
                n -= 3;
            }
            printf("\n");
        }
    }

    return 0;
}