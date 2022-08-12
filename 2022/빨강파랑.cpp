#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
#include <deque>
#include <map>
#include <numeric>

class SegTree {
private:
    using Bucket = std::pair<int, int>;
    int originCount;
    std::vector<Bucket> tree;
    std::vector<int> lazy;
    std::function<Bucket(const Bucket&, const Bucket&)> reduce;
    
    void initialize(int index, int start, int end) {
        if (start == end) {
            tree[index] = std::make_pair(0, start);
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid);
            initialize(index*2+1, mid+1, end);
            tree[index] = reduce(tree[index*2], tree[index*2+1]);
        }
    }

    void propagate(int index, int start, int end) {
        if (lazy[index]) {
            tree[index].first += lazy[index];
            if (start < end) {
                lazy[index*2] += lazy[index];
                lazy[index*2+1] += lazy[index];
            }
            lazy[index] = 0;
        }
    }

    Bucket query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);
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

    void update(int add, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            lazy[index] += add;
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(add, index*2, reqStart, reqEnd, treeStart, treeMed);
            update(add, index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
            tree[index] = reduce(tree[index*2], tree[index*2+1]);
        }
    }

public:
    SegTree(int count, bool isMinTree) {
        reduce = isMinTree ?
            [](const Bucket& b1, const Bucket& b2) { return std::min(b1, b2); } : 
            [](const Bucket& b1, const Bucket& b2) { return std::max(b1, b2); };
        
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
        initialize(1, 0, originCount-1);
    }

    Bucket query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, int add) {
        update(add, 1, start, end, 0, originCount-1);
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m, w, h;
    std::cin >> n >> m >> w >> h;
    std::map<int, std::vector<std::pair<int, int>>> points;
    std::vector<int> xVals, yVals;

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[x].emplace_back(y, 1);
        xVals.push_back(x);
        yVals.push_back(y);
        yVals.push_back(y+h);
        yVals.push_back(y+h+1);
    }

    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[x].emplace_back(y, -1);
        xVals.push_back(x);
        yVals.push_back(y);
        yVals.push_back(y+h);
        yVals.push_back(y+h+1);
    }

    std::sort(xVals.begin(), xVals.end());
    xVals.erase(std::unique(xVals.begin(), xVals.end()), xVals.end());
    std::sort(yVals.begin(), yVals.end());
    yVals.erase(std::unique(yVals.begin(), yVals.end()), yVals.end());

    SegTree minTree(yVals.size(), true);
    SegTree maxTree(yVals.size(), false);
    std::deque<int> inTree;

    auto addRange = [&](int y, int add) {
        int start = std::lower_bound(yVals.begin(), yVals.end(), y) - yVals.begin();
        int end = std::upper_bound(yVals.begin(), yVals.end(), y+h) - yVals.begin() - 1;
        minTree.update(start, end, add);
        maxTree.update(start, end, add);
    };

    auto queryMaxDiff = [&](int x) {
        auto min = minTree.query(0, yVals.size()-1);
        auto max = maxTree.query(0, yVals.size()-1);
        min.first = std::abs(min.first);
        max.first = std::abs(max.first);
        auto [qDiff, qTop] = std::max(min, max);
        return std::make_tuple(qDiff, x, yVals[qTop]-h);
    };

    std::tuple<int, int, int> maxDiff = { 0, -w, -h };
    for (const auto& [x, ps] : points) {
        while (inTree.size() && inTree.front() < x-w) {
            int ax = inTree.front();
            inTree.pop_front();
            for (auto [ay, add] : points[ax]) {
                addRange(ay, -add);
            }
            if (ax+1+w < x) {
                maxDiff = std::max(maxDiff, queryMaxDiff(ax+1));
            }
        }

        for (const auto& p : ps) {
            auto [ay, add] = p;
            addRange(ay, add);
        }
        inTree.push_back(x);
        maxDiff = std::max(maxDiff, queryMaxDiff(x-w));
    }
    while (inTree.size()) {
        int x = inTree.front();
        inTree.pop_front();
        for (auto [y, add] : points[x]) {
            addRange(y, -add);
        }
        maxDiff = std::max(maxDiff, queryMaxDiff(x+1));
    }

    auto [maxVal, x, y] = maxDiff;
    std::cout << maxVal << "\n" << x << " " << y << "\n";

    return 0;
}