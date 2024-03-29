#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using Range = std::tuple<int, int, int>;
using Selector = std::function<int(const Range&)>;
auto selectLeft  = [](const Range& r) { return std::get<0>(r); };
auto selectRight = [](const Range& r) { return std::get<1>(r); };

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    std::function<T(T, T)> reduce;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = reduce(tree[index*2], tree[index*2+1]);
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        reqStart = std::max(reqStart, treeStart);
        reqEnd = std::min(reqEnd, treeEnd);
        if (reqStart == treeStart && treeEnd == reqEnd) {
            return tree[index];
        }

        int treeMid = (treeStart+treeEnd)/2;
        bool left = !(treeMid < reqStart);
        bool right = !(reqEnd <= treeMid);

        if (left && right) {
            return reduce(query(index*2, reqStart, reqEnd, treeStart, treeMid),
                          query(index*2+1, reqStart, reqEnd, treeMid+1, treeEnd));
        } else if (left) {
            return query(index*2, reqStart, reqEnd, treeStart, treeMid);
        } else {
            return query(index*2+1, reqStart, reqEnd, treeMid+1, treeEnd);
        }
    }

    void update(T add, int index, int reqPos, int treeStart, int treeEnd) {
        if (treeStart == reqPos && treeEnd == reqPos) {
            tree[index] += add;
        } else if (treeStart <= reqPos && reqPos <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(add, index*2, reqPos, treeStart, treeMed);
            update(add, index*2+1, reqPos, treeMed+1, treeEnd);
            tree[index] = reduce(tree[index*2], tree[index*2+1]);
        }
    }

public:
    SegTree(int count, std::function<T(T, T)> reduce) : reduce(reduce) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int pos, T add) {
        update(add, 1, pos, 0, originCount-1);
    }
};

bool refineSide(int n, std::vector<Range>& ranges, bool leftToRight) {
    Selector pivotSel = selectLeft, secondSel = selectRight;
    int sweepStart = 1, sweepEnd = n, sweepInc = 1;
    if (!leftToRight) {
        std::swap(pivotSel, secondSel);
        std::swap(sweepStart, sweepEnd);
        sweepInc = -sweepInc;
    }

    std::vector<std::vector<Range>> side(n+1);
    for (int i = 0; i < ranges.size(); ++i) {
        side[pivotSel(ranges[i])].push_back(ranges[i]);
    }

    for (int l = sweepStart; l-sweepInc != sweepEnd; l += sweepInc) {
        if (side[l].empty()) {
            continue;
        }

        std::sort(side[l].begin(), side[l].end(), [&](const Range& r1, const Range& r2) -> bool {
            return std::abs(pivotSel(r1) - secondSel(r1)) < std::abs(pivotSel(r2) - secondSel(r2));
        });
        std::vector<Range> splited;
        splited.push_back(side[l].front());

        for (int i = 0; i+1 < side[l].size(); ++i) {
            if (secondSel(side[l][i]) == secondSel(side[l][i+1]) && std::get<2>(side[l][i]) != std::get<2>(side[l][i+1])) {
                return false;
            }

            if (secondSel(side[l][i]) != secondSel(side[l][i+1])) {
                auto [prevL, prevR, prevX] = side[l][i];
                auto [nextL, nextR, nextX] = side[l][i+1];
                int newL, newR;
                if (prevL == nextL) {
                    newL = prevR+1;
                    newR = nextR;
                } else {
                    newL = nextL;
                    newR = prevL-1;
                }
                splited.emplace_back(newL, newR, prevX ^ nextX);
            }
        }

        side[l].clear();
        for (auto& range : splited) {
            int newPivot = pivotSel(range);
            side[newPivot].push_back(range);
        }
    }

    ranges.clear();
    for (int i = 0; i <= n; ++i) {
        for (auto range : side[i]) {
            ranges.push_back(range);
        }
    }
    return true;
}

bool removeOverlapping(int n, std::vector<Range>& ranges) {
    if (refineSide(n, ranges, true)) {
        return refineSide(n, ranges, false);
    }
    return false;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Range> ranges(m);
    for (int i = 0; i < m; ++i) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        ranges[i] = { l, r, x };
    }

    if (removeOverlapping(n, ranges)) {
        std::sort(ranges.begin(), ranges.end(), [](const Range& r1, const Range& r2) { return selectRight(r1) < selectRight(r2); });
        SegTree<int> xorTree(n+1, std::bit_xor<int>());

        for (auto range : ranges) {
            auto [l, r, x] = range;
            xorTree.update(r, xorTree.query(l, r) ^ x);
        }
        for (int i = 1; i <= n; ++i) {
            printf("%d ", xorTree.query(i, i));
        }
    } else {
        printf("-1");
    }

    return 0;
}