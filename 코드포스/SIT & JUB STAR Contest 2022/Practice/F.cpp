#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string line;
    std::cin >> line;

    if (line.front() == '0') {
        std::cout << -1;
        return 0;
    }

    int count = 0;
    int last = -1;
    for (int i = 0; i < line.size(); ++i) {
        if ((line[i]-'0') % 2 == 1 && (line.size() == i+1 || line[i+1] != '0')) {
            ++count;
            last = i;
        }
    }
    if (last == line.size()-1) {
        std::cout << count;
    } else {
        std::cout << -1;
    }

    return 0;
}