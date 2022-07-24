#include <iostream>
#include <vector>
#include <map>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::set<int>> rangesByStart(1000001);
    std::vector<std::set<int, std::greater<int>>> rangesByEnd(1000001);
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        rangesByStart[a].insert(b);
        rangesByEnd[b].insert(a);
    }

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;

        if (rangesByStart[l].count(r)) {
            std::cout << "1\n";
        } else if (rangesByStart[l].lower_bound(r) != rangesByStart[l].end() && rangesByEnd[r].lower_bound(l) != rangesByEnd[r].end()) {
            std::cout << "2\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}