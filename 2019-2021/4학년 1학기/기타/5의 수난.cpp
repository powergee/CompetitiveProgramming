#include <iostream>
#include <string>

int main() {
    std::string line;
    std::cin >> line;
    int result = 0;
    for (char ch : line) {
        int a = (ch-'0');
        result += a*a*a*a*a;
    }
    std::cout << result;

    return 0;
}