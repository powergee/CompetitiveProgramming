#include <iostream>

int main() {
    int n, a, x, y;
    scanf("%d %d %d %d", &n, &a, &x, &y);

    if (n > a) {
        printf("%d", a*x + (n-a)*y);
    } else {
        printf("%d", n*x);
    }

    return 0;
}