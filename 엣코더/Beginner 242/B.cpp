#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string line;
    std::cin >> line;
    std::sort(line.begin(), line.end());
    std::cout << line;

    return 0;
}