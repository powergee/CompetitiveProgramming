#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int r;
        scanf("%d", &r);

        if (1900 <= r) {
            printf("Division 1\n");
        } else if (1600 <= r) {
            printf("Division 2\n");
        } else if (1400 <= r) {
            printf("Division 3\n");
        } else {
            printf("Division 4\n");
        }
    }

    return 0;
}