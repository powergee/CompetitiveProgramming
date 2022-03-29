#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, b, x, y;
        scanf("%lld %lld %lld %lld", &n, &b, &x, &y);

        Long total = 0;
        std::vector<Long> seq(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            if (seq[i-1] + x <= b) {
                seq[i] = seq[i-1] + x;
            } else {
                seq[i] = seq[i-1] - y;
            }
            total += seq[i];
        }

        printf("%lld\n", total);
    }

    return 0;
}