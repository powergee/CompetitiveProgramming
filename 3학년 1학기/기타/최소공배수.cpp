#include <iostream>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);
        int gcd = std::gcd(a, b);
        printf("%d\n", a*b/gcd);
    }

    return 0;
}