#include <iostream>
#include <numeric>

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);

    long long gcd = std::gcd(a, b);
    printf("%lld", a/gcd*b);

    return 0;
}