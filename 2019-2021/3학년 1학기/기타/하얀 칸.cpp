#include <iostream>
#include <string>

int main() {
    int index = 0, count = 0;
    for (int i = 0; i < 8; ++i) {
        std::string line;
        std::cin >> line;

        for (char ch : line) {
            ++index;
            if (ch == 'F' && index % 2 == 1) {
                ++count;
            }
        }
        ++index;
    }

    std::cout << count;

    return 0;
}