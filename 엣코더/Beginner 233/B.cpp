#include <iostream>
#include <string>
#include <algorithm>

int main() {
    int l, r;
    std::string s;
    std::cin >> l >> r >> s;

    std::reverse(s.begin()+l-1, s.begin()+r);
    std::cout << s;

    return 0;
}