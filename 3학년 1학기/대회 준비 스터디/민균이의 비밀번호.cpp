#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::set<std::string> words;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;

        std::string reve = word;
        std::reverse(reve.begin(), reve.end());
        
        if (words.find(reve) != words.end() || word == reve) {
            std::cout << reve.size() << " ";
            std::cout << reve[reve.size() / 2];
            break;
        }

        words.insert(word);
    }

    return 0;
}