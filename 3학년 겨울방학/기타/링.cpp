#include <iostream>
#include <numeric>

int main() {
    int n;
    scanf("%d", &n);

    int first;
    scanf("%d", &first);
    for (int i = 1; i < n; ++i) {
        int other;
        scanf("%d", &other);
        int gcd = std::gcd(first, other);
        printf("%d/%d\n", first/gcd, other/gcd);
    }

    return 0;
}