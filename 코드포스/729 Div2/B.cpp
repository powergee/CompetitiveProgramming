#include <iostream>

using Long = long long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, a, b;
        scanf("%lld %lld %lld", &n, &a, &b);

        bool yes = false;
        Long coef = 1;
        while (coef < INT32_MAX) {
            if (n >= coef && (n - coef) % b == 0) {
                yes = true;
                break;
            }
            if (a == 1) {
                break;
            } else {
                coef *= a;
            }
        }

        if (yes) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}