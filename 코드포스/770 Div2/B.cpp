#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long x, y, n;
        scanf("%lld %lld %lld", &n, &x, &y);

        for (int i = 0; i < n; ++i) {
            Long val;
            scanf("%lld", &val);
            x ^= val;
        }
        
        if (x%2 == y%2) {
            printf("Alice\n");
        } else {
            printf("Bob\n");
        }
    }

    return 0;
}