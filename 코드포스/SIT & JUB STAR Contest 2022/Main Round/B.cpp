#include <iostream>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int c, d;
    scanf("%d %d", &c, &d);

    if (c+d <= a || c+d <= b || (c <= a && d <= b) || (c <= b && d <= a)) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}