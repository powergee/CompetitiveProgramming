#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

struct Trie {
    Trie *next[2];
    Trie *fail;
    int matched = 0;

    Trie() {
        std::fill(next, next + 2, nullptr);
    }

    ~Trie() {
        for (int i = 0; i < 2; i++) {
            if (next[i]) {
                delete next[i];
            }
        }
    }

    void insert(std::string &str, int start) {
        if ((int)str.size() <= start) {
            matched += 1;
            return;
        }
        int nextIdx = str[start] - '0';
        if (!next[nextIdx]) {
            next[nextIdx] = new Trie;
        }
        next[nextIdx]->insert(str, start + 1);
    }

    void buildFail() {
        std::queue<Trie *> q;
        this->fail = this;
        q.push(this);

        while (!q.empty()) {
            Trie *current = q.front();
            q.pop();

            for (int i = 0; i < 2; i++) {
                Trie *next = current->next[i];

                if (!next) {
                    continue;
                } else if (current == this) {
                    next->fail = this;
                } else {
                    Trie *dest = current->fail;
                    while (dest != this && !dest->next[i]) {
                        dest = dest->fail;
                    }
                    if (dest->next[i]) {
                        dest = dest->next[i];
                    }
                    next->fail = dest;
                }

                if (next->fail->matched) {
                    next->matched += next->fail->matched;
                }
                q.push(next);
            }
        }
    }

    int find(std::string &query) {
        Trie *current = this;
        int result = 0;

        for (int c = 0; c < (int)query.size(); c++) {
            int nextIdx = query[c] - '0';
            while (current != this && !current->next[nextIdx]) {
                current = current->fail;
            }
            if (current->next[nextIdx]) {
                current = current->next[nextIdx];
            }
            if (current->matched) {
                result += current->matched;
            }
        }
        return result;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int b;
    std::cin >> b;

    Trie lowTrie, highTrie;
    for (bool isHigh : { false, true }) {
        for (int i = 0; i < b; ++i) {
            std::string check;
            std::cin >> check;
            (isHigh ? highTrie : lowTrie).insert(check, 0);
        }
    }

    lowTrie.buildFail();
    highTrie.buildFail();

    int n;
    std::cin >> n;

    while (n--) {
        std::string input;
        std::cin >> input;

        int currHeight = highTrie.find(input) - lowTrie.find(input);
        if (currHeight > 0) {
            std::cout << "LOW " << currHeight << "\n";
        } else if (currHeight < 0) {
            std::cout << "HIGH " << -currHeight << "\n";
        } else {
            std::cout << "GOOD\n";
        }
    }

    return 0;
}