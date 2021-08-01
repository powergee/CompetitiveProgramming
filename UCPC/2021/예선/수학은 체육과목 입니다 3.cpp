#include <iostream>
#include <string>

int isValid(std::string& line, int index, int expected) {
    std::string exStr = std::to_string(expected);
    if (line.size() < index+exStr.size()) {
        return 0;
    } else if (line.substr(index, exStr.size()) == exStr) {
        return (index+exStr.size() < line.size()) ? isValid(line, index+exStr.size(), expected+1) : expected;
    }

    return 0;
}

int main() {
    std::string line;
    std::cin >> line;

    for (int i = 1; ; ++i) {
        int expected = std::stoi(line.substr(0, i));
        int valid = isValid(line, 0, expected);
        if (valid) {
            std::cout << expected << " " << valid;
            break;
        }
    }

    return 0;
}