#include <iostream>

int main() {
    int X, Y, p1, p2;
    scanf("%d %d %d %d", &X, &Y, &p1, &p2);

    for (int a = 0; a <= 10000; ++a) {
        if ((X * a + p1 - p2) >= 0 && (X * a + p1 - p2) % Y == 0) {
            printf("%d", p1 + a * X);
            return 0;
        }
    }

    printf("-1");
    return 0;
}