#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    int a, b;
    std::cin >> a >> b;
    std::swap(str[a-1], str[b-1]);
    std::cout << str;

    return 0;
}