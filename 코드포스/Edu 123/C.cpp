#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#include <cmath>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    std::vector<T> lazy;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = std::max(tree[index*2], tree[index*2+1]);
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

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return std::max(query(index*2, reqStart, reqEnd, treeStart, treeMed),
                            query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd));
        } else {
            return INT32_MIN;
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
            tree[index] = std::max(tree[index*2], tree[index*2+1]);
        }
    }

public:
    SegTree(const std::vector<T>& original) {
        originCount = (int)original.size();
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
        initialize(1, 0, originCount-1, original);
    }

    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, T add) {
        update(add, 1, start, end, 0, originCount-1);
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, x;
        scanf("%d %d", &n, &x);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::vector<int> windows(n+1);
        for (int k = 0; k <= n; ++k) {
            int window = std::accumulate(arr.begin(), arr.begin()+k, 0);
            int maxWindow = window;
            for (int i = k; i < n; ++i) {
                window += arr[i];
                window -= arr[i-k];
                maxWindow = std::max(maxWindow, window);
            }
            windows[k] = maxWindow;
        }

        SegTree<int> maxTree(windows);
        printf("%d", maxTree.query(0, n));

        for (int k = 1; k <= n; ++k) {
            maxTree.update(k, n, x);
            printf(" %d", maxTree.query(0, n));
        }
        printf("\n");
    }

    return 0;
}