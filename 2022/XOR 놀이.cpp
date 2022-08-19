#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <set>
#include <functional>
#include <cassert>
#define BIT_WIDTH 24

struct Trie {
    Trie* next[2];
    int size = 0;
    std::set<int> bucket;

    Trie() {
        std::fill(next, next + 2, nullptr);
    }

    ~Trie() {
        for (int i = 0; i < 2; ++i) {
            if (next[i]) {
                delete next[i];
            }
        }
    }

    void insert(int val, int id, int binIndex=BIT_WIDTH) {
        size++;
        if (binIndex == -1) {
            bucket.insert(id);
        } else {
            int bit = (val&(1<<binIndex)) ? 1 : 0;
            if (next[bit] == nullptr) {
                next[bit] = new Trie;
            }
            next[bit]->insert(val, id, binIndex-1);
        }
    }

    void erase(int val, int id, int binIndex=BIT_WIDTH) {
        size--;
        if (binIndex == -1) {
            bucket.erase(id);
        } else {
            int bit = (val&(1<<binIndex)) ? 1 : 0;
            next[bit]->erase(val, id, binIndex-1);
        }
    }

    int findMinXor(int xorOp, int binIndex=BIT_WIDTH) {
        Trie* pro = (xorOp&(1<<binIndex)) ? next[1] : next[0];
        Trie* alt = (xorOp&(1<<binIndex)) ? next[0] : next[1];
        if (pro != nullptr && pro->size) {
            return pro->findMinXor(xorOp, binIndex-1);
        } else if (alt != nullptr && alt->size) {
            return alt->findMinXor(xorOp, binIndex-1);
        } else {
            assert(bucket.size() > 0);
            return *bucket.begin();
        }
    }

    int findMaxXor(int xorOp, int binIndex=BIT_WIDTH) {
        Trie* pro = (xorOp&(1<<binIndex)) ? next[0] : next[1];
        Trie* alt = (xorOp&(1<<binIndex)) ? next[1] : next[0];
        if (pro != nullptr && pro->size) {
            return pro->findMaxXor(xorOp, binIndex-1);
        } else if (alt != nullptr && alt->size) {
            return alt->findMaxXor(xorOp, binIndex-1);
        } else {
            assert(bucket.size() > 0);
            return *bucket.begin();
        }
    }

    int findXor(int xorOp, bool isMin) {
        return isMin ? findMinXor(xorOp) : findMaxXor(xorOp);
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    const int BLOCK = 1500;

    std::vector<int> arr(n);
    Trie bucket[n/BLOCK+1];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        bucket[i/BLOCK].insert(arr[i], i);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int op;
        std::cin >> op;

        if (op == 1 || op == 2) {
            int l, r, x;
            std::cin >> l >> r >> x;
            l--; r--;
            int gl = l/BLOCK;
            int gr = r/BLOCK;
            
            auto compare = op == 1 ? 
                [](int a, int b) { return a < b; } : 
                [](int a, int b) { return a > b; };
            
            int answerValue = arr[l] ^ x, answerIndex = l;
            if (gl == gr) {
                for (int i = l; i <= r; ++i) {
                    if (compare((arr[i] ^ x), answerValue)) {
                        answerValue = (arr[i] ^ x);
                        answerIndex = i;
                    }
                }
            } else {
                for (int i = l; i < (gl+1)*BLOCK; ++i) {
                    if (compare((arr[i] ^ x), answerValue)) {
                        answerValue = (arr[i] ^ x);
                        answerIndex = i;
                    }
                }
                for (int i = gl+1; i <= gr-1; ++i) {
                    int currIndex = bucket[i].findXor(x, op == 1);
                    if (compare((arr[currIndex] ^ x), answerValue)) {
                        answerValue = (arr[currIndex] ^ x);
                        answerIndex = currIndex;
                    }
                }
                for (int i = gr*BLOCK; i <= r; ++i) {
                    if (compare((arr[i] ^ x), answerValue)) {
                        answerValue = (arr[i] ^ x);
                        answerIndex = i;
                    }
                }
            }
            std::cout << answerIndex+1 << "\n";
        } else {
            int p, x;
            std::cin >> p >> x;
            p--;
            bucket[p/BLOCK].erase(arr[p], p);
            arr[p] = x;
            bucket[p/BLOCK].insert(arr[p], p);
        }
    }

    return 0;
}