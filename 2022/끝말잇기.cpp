#include <iostream>
#include <vector>
#include <set>

int main() {
    int n;
    std::cin >> n;

    std::set<char> terminals;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        terminals.insert(word.front());
        terminals.insert(word.back());
    }

    std::cout << (terminals.size() == 1 ? 1 : 0);

    return 0;
}