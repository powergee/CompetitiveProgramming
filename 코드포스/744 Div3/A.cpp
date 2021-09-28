#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;
    
    while (T--) {
        std::string str;
        std::cin >> str;

        int a = 0, b = 0, c = 0;
        for (char ch : str) {
            switch (ch)
            {
            case 'A': a++; break;
            case 'B': b++; break;
            case 'C': c++; break;
            }
        }

        if (b == a+c) {
            std::cout << "YES" << "\n";
        } else {
            std::cout << "NO" << "\n";
        }
    }

    return 0;
}