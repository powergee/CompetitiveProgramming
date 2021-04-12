#include <iostream>
#include <algorithm>

int getMaxDiv(int n) {
    int div = 2;
    while (n >= 2 && div*div <= n) {
        if (n % div == 0) {
            n /= div;
        } else {
            ++div;
        }
    }

    return std::max(div, n);
}

int main() {
    int n, k;
    scanf("%d\n%d", &n, &k);

    int count = 0;
    for (int i = 2; i <= n; ++i) {
        if (getMaxDiv(i) <= k) {
            ++count;
        }
    }

    printf("%d", count+1);

    return 0;
}