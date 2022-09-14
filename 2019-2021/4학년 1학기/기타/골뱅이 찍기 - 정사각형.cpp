#include <iostream>

int main() {
    int n;
    std::cin >> n;

    std::cout << std::string(n+2, '@') << "\n";
    for (int i = 0; i < n; ++i) {
        std::string line(n+2, ' ');
        line.front() = line.back() = '@';
        std::cout << line << "\n";
    }
    std::cout << std::string(n+2, '@') << "\n";

    return 0;
}