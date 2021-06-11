#include <iostream>
#include <string>

bool allNine(std::string digits) {
    for (char ch : digits) {
        if (ch != '9') {
            return false;
        }
    }
    return true;
}

int getSum(int bound) {
    if (bound < 0) {
        return 0;
    }
    if (bound < 10) {
        const int table[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 10 };
        return table[bound];
    }
    

    std::string digits = std::to_string(bound);
    std::string ones = digits;

    for (int i = 0; i < ones.size(); ++i) {
        ones[i] = '1';
    }
    
    if (allNine(digits)) {
        ones += '0';
        return std::stoi(ones);
    } else {
        return std::stoi(ones) * (digits[0]-'0') + getSum(std::stoi(digits.substr(1)));
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", getSum(b-1) - getSum(a-1));
    }

    return 0;
}