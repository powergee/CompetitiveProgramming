#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        long long n;
        scanf("%lld", &n);
        printf("%s\n", n % 10 ? "0" : "1");
    }

    return 0;
}