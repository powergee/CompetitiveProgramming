#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);

        if (n % 2 == 1 || n < 4) {
            printf("-1\n");
            continue;
        }

        Long min, max;
        for (Long i = 0; ; ++i) {
            Long spare = n - 4*i;
            if (spare % 6 == 0) {
                min = i+spare/6;
                break;
            }
        }
        for (Long i = 0; ; ++i) {
            Long spare = n - 6*i;
            if (spare % 4 == 0) {
                max = i+spare/4;
                break;
            }
        }

        printf("%lld %lld\n", min, max);
    }

    return 0;
}