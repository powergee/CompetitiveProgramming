#include <cstdio>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::map<std::string, int> count;
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cin >> name;
        count[name]++;
    }

    int maxCount = 0;
    std::string maxName;
    for (auto p : count) {
        if (maxCount < p.second) {
            maxCount = p.second;
            maxName = p.first;
        }
    }
    std::cout << maxName;

    return 0;
}
