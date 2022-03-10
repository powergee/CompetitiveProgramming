#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        if (n == 1) {
            printf("1\n");
        } else {
            printf("%lld\n", (1LL<<n)-1);
        }
    }

    return 0;
}