#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    if (str == "Hello,World!") {
        printf("AC");
    } else {
        printf("WA");
    }
    return 0;
}