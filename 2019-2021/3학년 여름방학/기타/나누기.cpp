#include <iostream>

int main() {
    int n, f;
    scanf("%d\n%d", &n, &f);

    for (int d2 = 0; d2 < 10; ++d2) {
        for (int d1 = 0; d1 < 10; ++d1) {
            int newVal = (n/100*100) + d2*10 + d1;
            if (newVal % f == 0) {
                printf("%d%d", d2, d1);
                return 0;
            }
        }
    }

    return 0;
}