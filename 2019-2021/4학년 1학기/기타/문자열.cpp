#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;

    while (T--) {
        std::string str;
        std::cin >> str;
        std::cout << str.front() << str.back() << "\n";
    }

    return 0;
}