#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string line;
    const std::string mo = "aeiou";
    std::getline(std::cin, line);

    for (int i = 0; i < line.size();) {
        std::cout << line[i];
        if (mo.find(line[i]) == std::string::npos) {
            i += 1;
        } else {
            i += 3;
        }
    }

    return 0;
}