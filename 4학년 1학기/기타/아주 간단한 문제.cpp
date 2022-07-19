#include <iostream>

int main() {
    int q;
    scanf("%d", &q);

    while (q--) {
        long long a, b;
        scanf("%lld %lld", &a, &b);

        if (b%a != 0 || b/a < 2) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }

    return 0;
}