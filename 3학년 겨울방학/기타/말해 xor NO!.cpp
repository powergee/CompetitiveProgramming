#include <iostream>

struct Trie {
    Trie* next[2];
    int keyCount = 0;

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

    void insert(int key, int e = (1<<30)) {
        keyCount++;
        if (e == 0) {
            return;
        }
        int index = (key & e) ? 1 : 0;
        if (!next[index]) {
            next[index] = new Trie;
        }
        next[index]->insert(key, e/2);
    }

    int countSmaller(int xorOp, int bound, int e = (1<<30)) {
        if (e == 1) {
            return ((bound & e) ? (next[0] ? next[0]->keyCount : 0) : 0);
        } else if (bound & e) {
            int s = (xorOp & e) ? 1 : 0;
            int b = (xorOp & e) ? 0 : 1;
            return (next[s] ? next[s]->keyCount : 0)
                 + (next[b] ? next[b]->countSmaller(xorOp, bound, e/2) : 0);
        } else if (xorOp & e) {
            return next[1] ? next[1]->countSmaller(xorOp, bound, e/2) : 0;
        } else {
            return next[0] ? next[0]->countSmaller(xorOp, bound, e/2) : 0;
        }
    }
};

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    Trie trie;
    for (int i = 0; i < n; ++i) {
        int a;
        scanf("%d", &a);
        trie.insert(a);
    }

    int answer = 0;
    for (int i = 0; i < m; ++i) {
        int b;
        scanf("%d", &b);
        answer += trie.countSmaller(b, k);
    }

    printf("%d", answer);

    return 0;
}