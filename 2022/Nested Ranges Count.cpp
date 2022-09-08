#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <set>

template <typename T>
class FenwickTree {
private:
    std::vector<T> tree;

public:
    T query(int end) {
        T result = 0;
        while (end > 0) {
            result += tree[end];
            end -= (end & -end);
        }
        return result;
    }

    void update(int pos, T add) {
        while (pos < int(tree.size())) {
            tree[pos] += add;
            pos += (pos & -pos);
        }
    }

    T query(int start, int end) {
        return query(end) - query(start-1);
    }

    FenwickTree(int count) {
        tree.resize(count+1, 0);
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<int> containsOther(n), otherContains(n);
    using Range = std::tuple<int, int, int>;
    std::vector<Range> ranges(n);
    std::vector<int> ys(n+1);

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        ranges[i] = { x, y, i };
        ys[i] = y;
    }
    ys.back() = 0;

    std::sort(ys.begin(), ys.end());
    ys.erase(std::unique(ys.begin(), ys.end()), ys.end());

    for (int i = 0; i < n; ++i) {
        auto [x, y, ri] = ranges[i];
        ranges[i] = {
            x,
            std::lower_bound(ys.begin(), ys.end(), y) - ys.begin(),
            ri
        };
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
        FenwickTree<int> yTree(ys.size());
        for (auto [x, y, i] : ranges) {
            containsOther[i] = yTree.query(y);
            yTree.update(y, 1);
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
        FenwickTree<int> yTree(ys.size());
        for (auto [x, y, i] : ranges) {
            otherContains[i] = yTree.query(y, ys.size());
            yTree.update(y, 1);
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