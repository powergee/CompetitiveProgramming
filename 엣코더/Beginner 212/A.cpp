#include <iostream>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    if (a == 0) {
        printf("Silver");
    } else if (b == 0) {
        printf("Gold");
    } else {
        printf("Alloy");
    }

    return 0;
}