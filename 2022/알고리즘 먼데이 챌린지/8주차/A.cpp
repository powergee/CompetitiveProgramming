#include <iostream>
#include <string>
#include <map>
#include <cassert>

const std::map<std::string, int> TABLE = {
    { "qw", 1 },
    { "as", 2 },
    { "zx", 3 },
    { "we", 4 },
    { "sd", 5 },
    { "xc", 6 },
    { "er", 7 },
    { "df", 8 },
    { "cv", 9 },
    { "ze", 0 },
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::string text;
    std::cin >> text;

    for (int i = 0; i+1 < n; ++i) {
        std::string token = text.substr(i, 2);
        if (TABLE.count(token)) {
            std::cout << TABLE.at(token);
        }
    }

    return 0;
}