#include <iostream>
#include <string>

bool isPalindrom(std::string str) {
    for (int i = 0, j = int(str.size())-1; i < j; ++i, --j) {
        if (str[i] != str[j]) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string str;
    std::cin >> str;
    auto left = str.find_first_not_of('a');
    auto right = str.find_last_not_of('a');
    if (std::string::npos == left) {
        printf(isPalindrom(str) ? "Yes" : "No");
    } else if ((left+1) > (str.size()-right)) {
        printf("No");
    } else {
        printf(isPalindrom(str.substr(left, right-left+1)) ? "Yes" : "No");
    }
    return 0;
}