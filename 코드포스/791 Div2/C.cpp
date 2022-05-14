#include <functional>
#include <vector>
#include <cmath>
#include <iostream>
#include <numeric>

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
};

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<int> rowCounter(n+1, 0), colCounter(n+1, 0);
    SegTree<int> rowTree(n+1, std::plus<int>()), colTree(n+1, std::plus<int>());

    while (q--) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            rowCounter[x]++;
            colCounter[y]++;
            if (rowCounter[x] == 1) {
                rowTree.update(x, 1);
            }
            if (colCounter[y] == 1) {
                colTree.update(y, 1);
            }
        } else if (t == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            rowCounter[x]--;
            colCounter[y]--;
            if (rowCounter[x] == 0) {
                rowTree.update(x, -1);
            }
            if (colCounter[y] == 0) {
                colTree.update(y, -1);
            }
        } else {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if (rowTree.query(x1, x2) == (x2-x1+1) || colTree.query(y1, y2) == (y2-y1+1)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }

    return 0;
}