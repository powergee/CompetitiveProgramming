#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>

using Number = std::pair<int, int>;
using Pair = std::pair<Number, Number>;

void solve() {
    int n;
    std::cin >> n;
    std::vector<Number> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].first;
        a[i].second = i;
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i].first;
        b[i].second = i;
    }

    std::vector<Pair> pairs(n);
    for (int i = 0; i < n; ++i) {
        pairs[i] = { a[i], b[i] };
    }
    std::sort(pairs.begin(), pairs.end(), [](Pair p1, Pair p2) -> bool {
        if (p1.first.first != p2.first.first) {
            return p1.first.first < p2.first.first;
        }
        return p1.second.first < p2.second.first;
    });

    auto satisfied = [](Pair n1, Pair n2) -> bool {
        return n1.first.first <= n2.first.first && n1.second.first <= n2.second.first;
    };

    bool possible = true;
    for (int i = 0; i+1 < n; ++i) {
        if (!satisfied(pairs[i], pairs[i+1])) {
            possible = false;
        }
    }
    
    if (!possible) {
        std::cout << "-1\n";
        return;
    }

    // std::cout << "Indexed\n";
    std::vector<int> indexes(n);
    for (int i = 0; i < n; ++i) {
        indexes[i] = pairs[i].first.second;
        // std::cout << indexes[i] << " ";
    }
    // std::cout << "\n";

    std::vector<std::pair<int, int>> answer;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j+1 < n; ++j) {
            if (indexes[j] > indexes[j+1]) {
                answer.emplace_back(j, j+1);
                std::swap(indexes[j], indexes[j+1]);
            }
        }
    }

    std::reverse(answer.begin(), answer.end());
    std::cout << answer.size() << "\n";
    for (auto [i, j] : answer) {
        std::cout << i+1 << " " << j+1 << "\n";
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }
    return 0;
}