#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        int a, b, c, p;
        std::cin >> a >> b >> c >> p;
        std::cout << ((a*b*c) % (p*p) == 0 && ((a % p == 0) + (b % p == 0) + (c % p == 0) >= 2)) << "\n";
    }

    return 0;
}