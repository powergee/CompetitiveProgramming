#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;

    if (a == 0) {
        std::cout << 0;
    } else if (a < 0) {
        std::cout << (b % 2 == 0 ? 1 : -1);
    } else {
        std::cout << 1;
    }

    return 0;
}