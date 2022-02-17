#include <iostream>
#include <string>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::set<char> VOWELS { 'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u' };
    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        std::string name;
        std::cin >> name;

        if (name.back() == 'y' || name.back() == 'Y') {
            std::cout << name << " is ruled by nobody.\n";
        } else if (VOWELS.count(name.back())) {
            std::cout << name << " is ruled by Alice.\n";
        } else {
            std::cout << name << " is ruled by Bob.\n";
        }
    }

    return 0;
}