#include <iostream>
#include <string>
#include <vector>
#include <map>

class Trie {
private:
    std::map<std::string, Trie*> next;

public:
    void insert(const std::vector<std::string>& words, int index=0) {
        if (index == words.size()) {
            return;
        }
        auto bucket = next.find(words[index]);
        if (bucket == next.end()) {
            Trie* t = new Trie;
            next[words[index]] = t;
            bucket = next.find(words[index]);
        }
        bucket->second->insert(words, index+1);
    }

    void print(int depth=0) {
        for (auto [word, t] : next) {
            std::cout << std::string(depth*2, '-') << word << "\n";
            t->print(depth+1);
        }
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    Trie root;

    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        std::vector<std::string> words(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> words[j];
        }
        root.insert(words);
    }
    root.print();

    return 0;
}