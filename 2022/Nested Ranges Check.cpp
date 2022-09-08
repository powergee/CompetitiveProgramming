#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <set>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<int> containsOther(n), otherContains(n);
    using Range = std::tuple<int, int, int>;
    std::vector<Range> ranges(n);

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        ranges[i] = { x, y, i };
    }

    { // Sweep 1 (containsOther)
        std::sort(ranges.begin(), ranges.end(), [&](const Range& r1, const Range& r2) {
            auto [x1, y1, i1] = r1;
            auto [x2, y2, i2] = r2;
            if (x1 != x2) {
                return x1 > x2;
            }
            return y1 < y2;
        });
        std::set<int, std::greater<int>> ySet;
        for (auto [x, y, i] : ranges) {
            containsOther[i] = ySet.lower_bound(y) != ySet.end();
            ySet.insert(y);
        }
    }

    { // Sweep 2 (otherContains)
        std::sort(ranges.begin(), ranges.end(), [&](const Range& r1, const Range& r2) {
            auto [x1, y1, i1] = r1;
            auto [x2, y2, i2] = r2;
            if (x1 != x2) {
                return x1 < x2;
            }
            return y1 > y2;
        });
        std::set<int, std::less<int>> ySet;
        for (auto [x, y, i] : ranges) {
            otherContains[i] = ySet.lower_bound(y) != ySet.end();
            ySet.insert(y);
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << containsOther[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < n; ++i) {
        std::cout << otherContains[i] << " ";
    }

    return 0;
}