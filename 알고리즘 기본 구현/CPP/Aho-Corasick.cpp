#include <algorithm>
#include <vector>
#include <queue>
#include <string>

struct Trie {
    Trie *next[26];
    Trie *fail;
    // 실제 매칭된 문자열이 필요하다면 아래 정의 사용
    // vector<string> outputs;
    // 매칭 여부만 필요하다면
    bool matched = false;

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
            // 실제 매칭된 문자열이 필요하다면 아래 정의 사용
            //outputs.push_back(str);
            // 매칭 여부만 필요하다면
            matched = true;
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

                // 실제 매칭된 문자열이 필요하다면 아래 정의 사용
                // if (next->fail->outputs.size() > 0) {
                //     next->outputs.insert(next->outputs.end(), current->outputs.begin(), current->outputs.end());
                // }
                // 매칭 여부만 필요하다면
                if (next->fail->matched) {
                    next->matched = true;
                }
                q.push(next);
            }
        }
    }

    bool find(std::string &query) {
        Trie *current = this;
        bool result = false;

        for (int c = 0; c < (int)query.size(); c++) {
            int nextIdx = query[c] - 'a';
            while (current != this && !current->next[nextIdx]) {
                current = current->fail;
            }
            if (current->next[nextIdx]) {
                current = current->next[nextIdx];
            }
            if (current->matched) {
                result = true;
                break;
            }
        }
        return result;
    }
};