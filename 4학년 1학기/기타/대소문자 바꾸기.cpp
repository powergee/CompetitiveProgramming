#include <iostream>
#include <string>

int main() {
    std::string input;
    std::cin >> input;
    for (char c : input) {
        if (isupper(c)) {
            std::cout << char(c + ('a' - 'A'));
        } else {
            std::cout << char(c + ('A' - 'a'));
        }
    }
    
    return 0;
}