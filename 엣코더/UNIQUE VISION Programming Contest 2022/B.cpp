#include <iostream>

int main() {
    long long a, b, k;
    std::cin >> a >> b >> k;
    int count = 0;
    while (a < b) {
        ++count;
        a *= k;
    }

    printf("%d", count);

    return 0;
}