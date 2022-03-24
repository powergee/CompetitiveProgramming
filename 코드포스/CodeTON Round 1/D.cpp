#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n;
        scanf("%lld", &n);
        if (__builtin_popcountll(n) == 1) {
            printf("-1\n");
        } else if (n % 2 == 1) {
            printf("2\n");
        } else {
            int e = 0;
            long long smallestOdd = n;
            while (smallestOdd % 2 == 0) {
                ++e;
                smallestOdd /= 2;
            }
            if (n/smallestOdd >= (smallestOdd+1)/2) {
                printf("%lld\n", smallestOdd);
            } else {
                printf("%lld\n", 1LL<<(e+1));
            }
        }
    }

    return 0;
}