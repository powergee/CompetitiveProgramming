#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long r, b, d;
        scanf("%lld %lld %lld", &r, &b, &d);

        long long min = std::min(r, b);
        long long max = std::max(r, b);

        if (min * (d+1) < max) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }

    return 0;
}