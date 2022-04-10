#include <iostream>
#include <string>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<std::string, std::string>> names(n);
    for (int i = 0; i < n; ++i) {
        std::string a, b;
        std::cin >> a >> b;
        names[i] = {a, b};
    }

    bool yes = true;
    for (int i = 0; i < n; ++i) {
        bool first = true, second = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            if (names[i].first == names[j].first || names[i].first == names[j].second) {
                first = false;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue;
            }
            if (names[i].second == names[j].first || names[i].second == names[j].second) {
                second = false;
            }
        }
        if (!first && !second) {
            yes = false;
        }
    }

    if (yes) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }

    return 0;
}