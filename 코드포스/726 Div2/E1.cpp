#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;

    std::string word;
    std::cin >> word;

    std::vector<std::string> cands;
    cands.reserve(n);

    for (int l = 1; l <= n; ++l) {
        std::string sub = word.substr(0, l);
        int mult = k / l + ((k % l) ? 1 : 0);
        std::string cand;
        cand.reserve(mult*sub.size());
        for (int i = 0; i < mult; ++i) {
            cand += sub;
        }
        cands.push_back(cand.substr(0, k));
    }

    std::cout << *std::min_element(cands.begin(), cands.end());

    return 0;
}