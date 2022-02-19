#include <iostream>

int main() {
    long long n;
    scanf("%lld", &n);

    long long a = std::abs(n);
    if (n < 0) {
        printf("%lld\n", -(a/10 + (a%10 ? 1 : 0)));
    } else {
        printf("%lld", a/10);
    }

    return 0;
}