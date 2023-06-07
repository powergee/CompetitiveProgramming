#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string str;
    int index;
    std::cin >> str >> index;
    std::cout << str[index-1] << "\n";
    return 0;
}