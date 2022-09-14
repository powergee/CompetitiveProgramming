#include <iostream>
#include <string>

int getDigitalRoot(std::string val) {
    int sum = 0;
    for (char ch : val) {
        sum += ch - '0';
    }
    
    if (sum < 10) {
        return sum;
    } else {
        return getDigitalRoot(std::to_string(sum));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string val;
    while (std::cin >> val, val != "0") {
        std::cout << getDigitalRoot(val) << "\n";
    }

    return 0;
}