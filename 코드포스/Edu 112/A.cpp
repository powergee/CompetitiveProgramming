#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n;
        scanf("%lld", &n);
        if (n % 2 == 1) {
            n++;
        }
        if (n >= 6) {
            printf("%lld\n", n/2*5);
        } else {
            printf("15\n");
        }
    }

    return 0;
}