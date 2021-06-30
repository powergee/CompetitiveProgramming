#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class SegTree {
private:
    int originCount;
    std::vector<int> tree;
    std::vector<int> lazy;
    
    void initialize(int index, int start, int end, const std::vector<int>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index * 2, start, mid, original);
            initialize(index * 2 + 1, mid + 1, end, original);
            tree[index] = tree[index*2] ^ tree[index*2+1];
        }
    }

    void propagate(int index, int start, int end) {
        if (lazy[index]) {
            if ((end - start + 1) % 2) {
                tree[index] ^= lazy[index];
            }
            if (start < end) {
                lazy[index*2] ^= lazy[index];
                lazy[index*2+1] ^= lazy[index];
            }
            lazy[index] = 0;
        }
    }

    int query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return query(index*2, reqStart, reqEnd, treeStart, treeMed)
                 ^ query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
        } else {
            return 0;
        }
    }

    void update(int val, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            lazy[index] ^= val;
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(val, index*2, reqStart, reqEnd, treeStart, treeMed);
            update(val, index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
            tree[index] = tree[index*2] ^ tree[index*2+1];
        }
    }

public:
    SegTree(const std::vector<int>& original) {
        originCount = (int)original.size();
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize, 0);
        lazy.resize(vecSize, 0);
        initialize(1, 0, originCount-1, original);
    }

    int query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, int val) {
        update(val, 1, start, end, 0, originCount-1);
    }
};

int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> original(n);

    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        original[i] = val;
    }
    SegTree tree(original);

    int q;
    scanf("%d", &q);
    while (q--) {
        int kind, i, j, k;
        scanf("%d", &kind);

        switch (kind)
        {
        case 1:
            scanf("%d %d %d", &i, &j, &k);
            tree.update(i, j, k);
            break;
        
        case 2:
            scanf("%d", &i);
            printf("%d\n", tree.query(i, i));
            break;
        }
    }
    
    return 0;
}