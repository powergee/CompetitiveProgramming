#include <iostream>
#include <string>
#include <vector>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int a, b;
    std::cin >> a >> b;
    
    std::vector<std::string> stations(a);
    for (int i = 0; i < a; ++i) {
        std::cin >> stations[i];
    }

    std::set<std::string> express;
    for (int i = 0; i < b; ++i) {
        std::string name;
        std::cin >> name;
        express.insert(name);
    }

    for (int i = 0; i < a; ++i) {
        if (express.find(stations[i]) != express.end()) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }

    return 0;
}