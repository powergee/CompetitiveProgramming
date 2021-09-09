#include <iostream>
#include <unordered_set>

bool isSurprising(std::string& word) {
    for (int d = 0; d < (int)word.size()-1; ++d) {
        std::unordered_set<std::string> pairs;
        for (int i = 0; i+d+1 < word.size(); ++i) {
            std::string pair;
            pair += word[i];
            pair += word[i+d+1];
            if (pairs.find(pair) == pairs.end()) {
                pairs.insert(pair);
            } else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string word;
    
    while ((std::cin >> word), word != "*") {
        if (isSurprising(word)) {
            std::cout << word << " is surprising.\n";
        } else {
            std::cout << word << " is NOT surprising.\n";
        }
    }

    return 0;
}