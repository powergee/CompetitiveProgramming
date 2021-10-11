#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cin >> input;

    std::cout << std::string(4-input.size(), '0') + input;

    return 0;
}