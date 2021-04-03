#include <iostream>
#include <string>

bool isPalin(std::string str) {
    for (int i = 0; i < (int)str.size()/2; ++i) {
        if (str[i] != str[int(str.size())-1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::string input;
        std::cin >> input;

        bool allA = true;
        for (char ch : input) {
            if (ch != 'a') {
                allA = false;
                break;
            }
        }

        if (allA) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
            if (!isPalin(input + 'a')) {
                std::cout << input + 'a' << "\n";
            } else {
                std::cout << 'a' + input << "\n";
            }
        }
    }
}