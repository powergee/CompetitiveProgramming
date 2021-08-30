#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int a = n / 3, b = n / 3;
        int remain = n % 3;
        if (remain == 1) {
            ++a;
        } else if (remain == 2) {
            ++b;
        }
        printf("%d %d\n", a, b);
    }

    return 0;
}