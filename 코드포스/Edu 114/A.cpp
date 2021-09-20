#include <iostream>
#include <string>

std::string getUnit(int len) {
    return std::string(len/2, '(') + std::string(len/2, ')');
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        if (n == 2) {
            std::cout << getUnit(2) << getUnit(2) << "\n";
            std::cout << getUnit(4) << "\n";
        } else {
            for (int i = 0; i < n; ++i) {
                std::cout << getUnit(i*2) + getUnit(2) + getUnit((n-i-1)*2);
                std::cout << "\n";
            }
        }
    }

    return 0;
}