#include <iostream>
#include <numeric>

using Long = long long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        printf((c <= std::max(a, b) && c % std::gcd(a, b) == 0) ? "YES\n" : "NO\n");
    }

    return 0;
}