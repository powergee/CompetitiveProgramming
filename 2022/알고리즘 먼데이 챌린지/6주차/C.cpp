#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string line;
    std::getline(std::cin, line);
    int T = std::stoi(line);

    while (T--) {
        std::string src, key;
        std::getline(std::cin, src);
        std::getline(std::cin, key);

        char kind = key[0];
        key = key.substr(2);
        for (int i = 0; i < src.size(); ++i) {
            if (!std::isalpha(src[i])) {
                continue;
            }

            int base = 'A' <= src[i] && src[i] <= 'Z' ? 'A' : 'a';
            int index = src[i] - base;
            int changed = index + key[i%key.size()] * (kind == 'E' ? 1 : -1);
            while (changed < 0) {
                changed += 26;
            }
            changed %= 26;
            src[i] = char(base + changed);
        }
        std::cout << src << "\n";
    }

    return 0;
}