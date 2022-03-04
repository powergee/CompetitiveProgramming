#include <iostream>

int main() {
    int n, T;
    scanf("%d %d", &n, &T);

    while (T--) {
        if (n % 2) {
            printf("1\n");
            printf("%d %d\n", n/2+1, n/2+1);
            fflush(stdout);
        } else {
            printf("2\n");
            fflush(stdout);
        }

        while (true) {
            int r, c;
            scanf("%d %d", &r, &c);
            if (r == 0 && c == 0) {
                break;
            }
            printf("%d %d\n", n+1-r, n+1-c);
            fflush(stdout);
        }
    }

    return 0;
}