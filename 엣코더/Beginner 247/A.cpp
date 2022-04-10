#include <iostream>
#include <string>

int main() {
    std::string line;
    std::cin >> line;
    line = "0" + line;
    line = line.substr(0, 4);
    std::cout << line;

    return 0;
}