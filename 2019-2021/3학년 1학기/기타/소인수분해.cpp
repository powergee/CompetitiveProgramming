#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    for (int div = 2; div*div <= n;) {
        if (n % div == 0) {
            printf("%d\n", div);
            n /= div;
        } else {
            ++div;
        }
    }

    if (n > 1) {
        printf("%d", n);
    }

    return 0;
}