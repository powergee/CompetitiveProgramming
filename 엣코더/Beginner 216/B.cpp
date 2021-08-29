#include <iostream>
#include <string>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    bool yes = false;
    std::set<std::string> names;
    for (int i = 0; i < n; ++i) {
        std::string s1, s2;
        std::cin >> s1 >> s2;
        std::string comb = s1 + "_" + s2;
        if (names.find(comb) != names.end()) {
            yes = true;
            break;
        }
        names.insert(comb);
    }

    if (yes) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }

    return 0;
}