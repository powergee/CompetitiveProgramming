#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

struct Trie {
    Trie *next[26];
    Trie *fail;
    int matched = 0;

    Trie() {
        std::fill(next, next + 26, nullptr);
    }

    ~Trie() {
        for (int i = 0; i < 26; i++) {
            if (next[i]) {
                delete next[i];
            }
        }
    }

    void insert(std::string &str, int start) {
        if ((int)str.size() <= start) {
            matched = str.size();
            return;
        }
        int nextIdx = str[start] - 'a';
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

            for (int i = 0; i < 26; i++) {
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
                    next->matched = std::max(next->matched, current->matched);
                }
                q.push(next);
            }
        }
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::string query;
    std::cin >> query;

    Trie trie;
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        trie.insert(word, 0);
    }
    trie.buildFail();

    Trie *current = &trie;

    std::vector<int> coverage(query.size(), 0);
    for (int c = 0; c < (int)query.size(); c++) {
        int nextIdx = query[c] - 'a';
        while (current != &trie && !current->next[nextIdx]) {
            current = current->fail;
        }
        if (current->next[nextIdx]) {
            current = current->next[nextIdx];
        }
        coverage[c] = current->matched;
    }

    int coverCount = 0;
    int currPos = query.size()-1;
    std::vector<bool> visited(query.size(), false);
    while (currPos >= 0) {
        int next = INT32_MAX;
        for (int p = currPos; p < query.size() && !visited[p]; ++p) {
            visited[p] = true;
            next = std::min(next, p-coverage[p]);
        }
        if (currPos <= next) {
            coverCount = -1;
            break;
        } else {
            currPos = next;
            ++coverCount;
        }
    }
    std::cout << coverCount;

    return 0;
}