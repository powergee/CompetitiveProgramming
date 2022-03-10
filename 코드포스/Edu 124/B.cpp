#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<Long> result(n);
        bool possible = true;
        result[0] = 1;
        for (int i = 1; i < n; ++i) {
            result[i] = result[i-1]*3;
            if (result[i] > 1000000000LL) {
                possible = false;
            }
        }

        if (possible) {
            printf("YES\n");
            for (int i = 0; i < n; ++i) {
                printf("%lld ", result[i]);
            }
            printf("\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}