#include <iostream>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        Long sum = 0;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            sum += val;
        }

        Long div = sum / n;
        Long spare = sum - div*n;
        printf("%lld\n", (n-spare) * spare);
    }

    return 0;
}