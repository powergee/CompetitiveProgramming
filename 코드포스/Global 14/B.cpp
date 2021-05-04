#include <iostream>
#include <cmath>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        if (n == 1) {
            printf("NO\n");
            continue;
        }

        int nEff = 0;
        while (n >= 2) {
            if (n % 2 == 0) {
                n /= 2;
                nEff++;
            } else {
                break;
            }
        }

        int sqrt = std::round(std::sqrt(n));
        if (sqrt*sqrt == n && nEff >= 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}