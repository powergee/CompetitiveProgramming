#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, k;
    std::cin >> n >> k;
    std::vector<std::pair<std::string, std::string>> people(n);

    for (int i = 0; i < n; ++i) {
        std::string name, height;
        std::cin >> name >> height;
        people[i] = { name, height };
    }

    std::sort(people.begin(), people.end(), [](auto s1, auto s2) {
        if (s1.first != s2.first) {
            return s1.first < s2.first;
        }
        return std::stod(s1.second) > std::stod(s2.second);
    });

    std::cout << people[k-1].first << " " << people[k-1].second;

    return 0;
}