#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string word;
    std::cin >> word;

    auto found = std::find_if(word.begin(), word.end(), [&](char ch) { return ch != word[0]; });
    if (found == word.end()) {
        std::cout << -1;
        return 0;
    }

    bool wholePalin = true;
    for (int i = 0; i <= word.size()/2; ++i) {
        if (word[i] != word[int(word.size())-1-i]) {
            wholePalin = false;
            break;
        }
    }

    if (wholePalin) {
        std::cout << int(word.size())-1;
    } else {
        std::cout << int(word.size());
    }

    return 0;
}