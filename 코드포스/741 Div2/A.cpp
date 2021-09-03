#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int l, r;
        scanf("%d %d", &l, &r);

        if (l == r) {
            printf("0\n");
        } else {
            int b = r;
            int a = std::max((b+1)/2 + ((b+1)%2 == 1 ? 1 : 0), l);
            printf("%d\n", b % a);
        }
    }

    return 0;
}