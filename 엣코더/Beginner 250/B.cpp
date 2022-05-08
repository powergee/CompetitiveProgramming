#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, a, b;
    std::cin >> n >> a >> b;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a; ++j) {
            for (int k = 0; k < n; ++k) {
                std::cout << std::string(b, ((i+k) % 2 == 0 ? '.' : '#'));
            }
            std::cout << "\n";
        }
    }

    return 0;
}