#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>

using Long = long long;

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

    int findLowerBound(T sum, int index, int treeStart, int treeEnd) {
        int treeMid = (treeStart+treeEnd) / 2;
        if (treeStart == treeEnd) {
            return treeStart;
        } else if (tree[index*2] < sum) {
            return findLowerBound(sum-tree[index*2], index*2+1, treeMid+1, treeEnd);
        } else {
            return findLowerBound(sum, index*2, treeStart, treeMid);
        }
    }

public:
    SegTree(int count, std::function<T(T, T)> reduce) : reduce(reduce) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
    }

    SegTree(const std::vector<T>& original, std::function<T(T, T)> reduce) : SegTree(original.size(), reduce) {
        initialize(1, 0, originCount-1, original);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int pos, T add) {
        update(add, 1, pos, 0, originCount-1);
    }

    int findLowerBound(T sum) {
        return findLowerBound(sum, 1, 0, originCount-1);
    }
};

int main() {
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    SegTree<int> maxTree(arr, [](int a, int b) { return std::max(a, b); });
    SegTree<int> minTree(arr, [](int a, int b) { return std::min(a, b); });

    // min이 처음으로 value 이하인 위치를 찾음.
    auto getLowerBoundOfMin = [&](int start, int value) -> int {
        if (value < minTree.query(start, n-1)) {
            return n;
        } else if (arr[start] <= value) {
            return start;
        }

        int left = start, right = n-1;
        while (left < right) {
            int mid = (left+right)/2;
            int minVal = minTree.query(start, mid);
            if (minVal <= value) {
                right = mid;
            } else {
                left = mid+1;
            }
        }

        return left;
    };

    // max가 처음으로 value 이상인 위치를 찾음.
    auto getLowerBoundOfMax = [&](int start, int value) -> int {
        if (maxTree.query(start, n-1) < value) {
            return n;
        } else if (value <= arr[start]) {
            return start;
        }

        int left = start, right = n-1;
        while (left < right) {
            int mid = (left+right)/2;
            int maxVal = maxTree.query(start, mid);
            if (value <= maxVal) {
                right = mid;
            } else {
                left = mid+1;
            }
        }

        return left;
    };

    Long count = 0;
    for (int i = 0; i < n; ++i) {
        std::pair<int, int> minRange = { getLowerBoundOfMin(i, y), getLowerBoundOfMin(i, y-1) };
        std::pair<int, int> maxRange = { getLowerBoundOfMax(i, x), getLowerBoundOfMax(i, x+1) };

        if (minRange.second-minRange.first == 0 || maxRange.second-maxRange.first == 0) {
            continue;
        } else if (minRange.second <= maxRange.first || maxRange.second <= minRange.first) {
            continue;
        }
        std::pair<int, int> intersect = { std::max(minRange.first, maxRange.first), std::min(minRange.second, maxRange.second) };
        count += intersect.second-intersect.first;
    }

    printf("%lld", count);

    return 0;
}