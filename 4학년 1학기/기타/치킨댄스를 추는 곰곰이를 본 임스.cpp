#include <iostream>

int main() {
    int n;
    scanf("%d", &n);
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", std::min(n, a/2+b));

    return 0;
}