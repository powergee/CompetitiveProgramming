#include <iostream>

int main() {
    int x ,y;
    scanf("%d %d", &x, &y);

    int diff = y-x < 0 ? 0 : y-x;
    printf("%d", diff / 10 + (diff % 10 ? 1 : 0));

    return 0;
}