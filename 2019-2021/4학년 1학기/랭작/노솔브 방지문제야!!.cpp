#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    std::cin >> q;

    while (q--) {
        int a;
        std::cin >> a;
        std::cout << (__builtin_popcount(a) == 1 ? 1 : 0) << "\n";
    }

    return 0;
}