#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::string input;
        std::cin >> input;

        int doubleDigits = -1;
        int singleDigit = INT32_MAX;
        for (int i = 0; i < int(input.size())-1; ++i) {
            int d1 = input[i] - '0';
            int d2 = input[i+1] - '0';
            int s = d1+d2;

            if (s >= 10) {
                doubleDigits = std::max(doubleDigits, i);
            } else {
                singleDigit = std::min(singleDigit, i);
            }
        }

        if (doubleDigits != -1) {
            int d1 = input[doubleDigits] - '0';
            int d2 = input[doubleDigits+1] - '0';
            int s = d1+d2;
            std::cout << input.substr(0, doubleDigits) << s << input.substr(doubleDigits+2) << "\n";
        } else {
            int d1 = input[singleDigit] - '0';
            int d2 = input[singleDigit+1] - '0';
            int s = d1+d2;
            std::cout << input.substr(0, singleDigit) << s << input.substr(singleDigit+2) << "\n";
        }
    }

    return 0;
}