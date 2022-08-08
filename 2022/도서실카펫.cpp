#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    std::vector<T> lazy;
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

    void propagate(int index, int start, int end) {
        if (lazy[index]) {
            tree[index] += lazy[index];
            if (start < end) {
                lazy[index*2] += lazy[index];
                lazy[index*2+1] += lazy[index];
            }
            lazy[index] = 0;
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
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

    void update(T add, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
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
    SegTree(int count, std::function<T(T, T)> reduce) : reduce(reduce) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
    }

    SegTree(const std::vector<T>& original, std::function<T(T, T)> reduce) : SegTree(original.size(), reduce) {
        initialize(1, 0, originCount-1, original);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, T add) {
        update(add, 1, start, end, 0, originCount-1);
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    using Point = std::pair<int, int>;
    using Range = std::pair<int, int>;
    Point origin, bound;
    std::cin >> origin.first >> bound.second >> bound.first >> origin.second;
    int width = bound.first - origin.first;
    int height = bound.second - origin.second;

    int carpetSize, stainCnt;
    std::cin >> carpetSize >> stainCnt;
    std::vector<std::vector<Range>> add(width+1), sub(width+1);

    for (int i = 0; i < stainCnt; ++i) {
        Point topLeft, bottomRight;
        std::cin >> topLeft.first >> topLeft.second >> bottomRight.first >> bottomRight.second;
        topLeft.first -= origin.first;
        topLeft.second -= origin.second;
        bottomRight.first -= origin.first;
        bottomRight.second -= origin.second;
        
        int left = topLeft.first;
        int right = bottomRight.first;
        int top = topLeft.second;
        int bottom = bottomRight.second;

        if (right-left <= carpetSize && top-bottom <= carpetSize) {
            int b = std::max(0, top-carpetSize);
            int t = bottom;
            add[right].emplace_back(b, t);
            if (carpetSize+left <= width) {
                sub[carpetSize+left].emplace_back(b, t);
            }
        }
    }

    int answer = 0;
    SegTree<int> maxTree(height+1, [](int a, int b) { return std::max(a, b); });
    for (int i = 0; i <= width; ++i) {
        for (auto [b, t] : add[i]) {
            maxTree.update(b, t, 1);
        }
        answer = std::max(answer, maxTree.query(0, height));
        for (auto [b, t] : sub[i]) {
            maxTree.update(b, t, -1);
        }
    }
    std::cout << answer << "\n";

    return 0;
}