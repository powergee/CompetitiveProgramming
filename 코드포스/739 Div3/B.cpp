#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        int dist = std::abs(a-b);
        int n = dist*2;
        if ((a+dist-1)%n+1 != b || c > n || a > n || b > n) {
            printf("-1\n");
        } else {
            printf("%d\n", (c+dist-1)%n+1);
        }
    }

    return 0;
}