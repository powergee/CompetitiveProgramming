#include <iostream>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    printf("%d", std::abs(a-b)+std::abs(b-c));

    return 0;
}