#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::cout << "int a;\n";
    for (int i = 1; i <= n; ++i) {
        std::cout << "int ";
        for (int j = 0; j < i; ++j) {
            std::cout << "*";
        }
        std::cout << "ptr";
        if (i > 1) {
            std::cout << i;
        }
        std::cout << " = ";

        if (i == 1) {
            std::cout << "&a;\n";
        } else if (i == 2) {
            std::cout << "&ptr;\n";
        } else {
            std::cout << "&ptr";
            std::cout << i-1;
            std::cout << ";\n";
        }
    }

    return 0;
}