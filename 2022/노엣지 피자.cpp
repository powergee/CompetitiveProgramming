#include <iostream>
#include <vector>
#include <map>
#include <set>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, l, q;
    std::cin >> n >> l >> q;

    std::map<int, int> pizza;
    std::map<int, std::multiset<int>> window;
    std::set<int> conflicts;
    Long answer = 0;

    auto eraseFromWindow = [&](int idx, int val) {
        if (conflicts.find(idx) == conflicts.end() && window[idx].size()) {
            answer -= *window[idx].begin();
        }
        window[idx].erase(window[idx].find(val));
        conflicts.erase(idx);

        if (window[idx].size() && *window[idx].begin() != *std::prev(window[idx].end())) {
            conflicts.insert(idx);
        } else if (window[idx].size()) {
            answer += *window[idx].begin();
        }
    };

    auto insertIntoWindow = [&](int idx, int val) {
        if (conflicts.find(idx) == conflicts.end() && window[idx].size()) {
            answer -= *window[idx].begin();
        }
        window[idx].insert(val);
        conflicts.erase(idx);

        if (window[idx].size() && *window[idx].begin() != *std::prev(window[idx].end())) {
            conflicts.insert(idx);
        } else if (window[idx].size()) {
            answer += *window[idx].begin();
        }
    };

    while (q--) {
        int op;
        std::cin >> op;

        if (op == 1) {
            int pos, val;
            std::cin >> pos >> val;
            if (pizza[pos]) {
                eraseFromWindow(pos%l, pizza[pos]);
            }
            insertIntoWindow(pos%l, val);
            pizza[pos] = val;
        } else {
            int pos;
            std::cin >> pos;
            eraseFromWindow(pos%l, pizza[pos]);
            pizza[pos] = 0;
        }

        if (conflicts.empty()) {
            std::cout << "YES " << answer << "\n";
        } else {
            std::cout << "NO" << "\n";
        }
    }

    return 0;
}