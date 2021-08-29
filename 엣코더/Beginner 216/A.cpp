#include <iostream>

int main() {
    int x, y;
    scanf("%d.%d", &x, &y);

    if (y <= 2) {
        printf("%d-", x);
    } else if (y <= 6) {
        printf("%d", x);
    } else {
        printf("%d+", x);
    }

    return 0;
}