#include <iostream>

int main() {
    int s, c1, c2, p;
    scanf("%d %d %d %d", &s, &c1, &c2, &p);

    printf("%d", c1 + (p > s ? (p-s)*c2: 0));

    return 0;
}