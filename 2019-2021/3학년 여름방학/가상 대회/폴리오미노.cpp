#include <iostream>

bool fillPoly(int length, std::string& answer) {
    if (length % 2 == 1) {
        return false;
    }

    int fourCount = length / 4;
    int twoCount = (length % 4) / 2;
    for (int i = 0; i < fourCount; ++i) {
        answer += "AAAA";
    }
    for (int i = 0; i < twoCount; ++i) {
        answer += "BB";
    }
    return true;
}

int main() {
    std::string str, answer;
    std::cin >> str;

    int currLength = 0;
    bool success = true;
    for (int i = 0; i < str.size() && success; ++i) {
        if (str[i] == 'X') {
            ++currLength;
        } else {
            success = fillPoly(currLength, answer);
            currLength = 0;
            answer += '.';
        }
    }
    if (currLength) {
        success = fillPoly(currLength, answer);
    }

    if (success) {
        std::cout << answer;
    } else {
        std::cout << -1;
    }

    return 0;
}