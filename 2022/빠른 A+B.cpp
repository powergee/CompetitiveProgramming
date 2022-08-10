#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << a + b << "\n";
    }

    return 0;
}