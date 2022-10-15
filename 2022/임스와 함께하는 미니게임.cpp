#include <iostream>
#include <string>
#include <set>
#include <map>

const std::map<char, int> NEED = {
    { 'Y', 2 },
    { 'F', 3 },
    { 'O', 4 }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    char kind;
    std::cin >> n >> kind;
    std::set<std::string> names;
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cin >> name;
        names.insert(name);
    }
    std::cout << names.size() / (NEED.at(kind)-1);

    return 0;
}