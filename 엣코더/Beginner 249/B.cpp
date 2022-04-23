#include <iostream>
#include <string>
#include <set>

int main() {
    std::string str;
    std::cin >> str;

    bool upper = false, lower = false, distinct = true;
    std::set<char> chSet;
    for (char ch : str) {
        if ('a' <= ch && ch <= 'z') {
            lower = true;
        }
        if ('A' <= ch && ch <= 'Z') {
            upper = true;
        }
        if (chSet.count(ch)) {
            distinct = false;
        }
        chSet.insert(ch);
    }

    if (upper && lower && distinct) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }
    
    return 0;
}