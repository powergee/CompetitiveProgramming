#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string a, b;
    std::cin >> a >> b;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());

    bool easy = true;
    for (int i = 0; i < std::min(a.size(), b.size()); ++i) {
        if ((a[i]-'0') + (b[i]-'0') > 9) {
            easy = false;
            break;
        }
    }

    if (easy) {
        std::cout << "Easy";
    } else {
        std::cout << "Hard";
    }

    return 0;
}
