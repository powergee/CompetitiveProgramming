#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <functional>

struct Trie {
    Trie* next[2];

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

    void insert(const char *key) {
        if (*key == '\0') {
            return;
        }
        int index = *key - '0';
        if (!next[index]) {
            next[index] = new Trie;
        }
        next[index]->insert(key + 1);
    }

    void insert(const std::string& key) {
        insert(key.c_str());
    }
};


int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        int n, m, p;
        std::cin >> n >> m >> p;

        std::vector<std::string> prefer(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> prefer[i];
        }

        Trie* trie = new Trie;
        for (int i = 0; i < m; ++i) {
            std::string rep;
            std::cin >> rep;
            trie->insert(rep);
        }

        std::vector<std::map<Trie*, int>> dp(p+1);

        std::function<int(int, Trie*)> getMinComplain = [&](int index, Trie* forbidden) -> int {
            if (index == p) {
                return (forbidden ? INT32_MAX/2 : 0);
            }
            if (dp[index].count(forbidden)) {
                return dp[index][forbidden];
            }

            int result = INT32_MAX/2;
            for (char curr = '0'; curr <= '1'; ++curr) {
                int complain = 0;
                for (int i = 0; i < n; ++i) {
                    if (prefer[i][index] != curr) {
                        ++complain;
                    }
                }
                Trie* next = (forbidden ? forbidden->next[curr-'0'] : nullptr);
                result = std::min(result, complain + getMinComplain(index+1, next));
            }
            return dp[index][forbidden] = result;
        };

        std::cout << getMinComplain(0, trie) << "\n";
        delete trie;
    }

    return 0;
}