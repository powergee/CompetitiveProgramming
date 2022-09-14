#include <iostream>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int c;
    scanf("%d", &c);

    int total = 60*a+b+c;
    printf("%d %d", (total/60)%24, total%60);

    return 0;
}