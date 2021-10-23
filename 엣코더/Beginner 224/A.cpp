#include <iostream>

int main() {
    std::string str;
    std::cin >> str;

    if (str.size() >= 3 && str.substr(str.size()-3) == "ist") {
        printf("ist");
    } else {
        printf("er");
    }

    return 0;
}