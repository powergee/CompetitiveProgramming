#include <iostream>
#include <vector>
#include <cmath>
#define MOD 1000000007

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    
    void initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index*2, start, mid, original);
            initialize(index*2+1, mid+1, end, original);
            tree[index] = (tree[index*2] * tree[index*2+1]) % MOD;
        }
    }

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return (query(index*2, reqStart, reqEnd, treeStart, treeMed)
                  * query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd)) % MOD;
        } else {
            return 1;
        }
    }

    void update(T newVal, int index, int reqPos, int treeStart, int treeEnd) {
        if (treeStart == reqPos && treeEnd == reqPos) {
            tree[index] = newVal;
        } else if (treeStart <= reqPos && reqPos <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(newVal, index*2, reqPos, treeStart, treeMed);
            update(newVal, index*2+1, reqPos, treeMed+1, treeEnd);
            tree[index] = (tree[index*2] * tree[index*2+1]) % MOD;
        }
    }

public:
    SegTree(const std::vector<T>& original) {
        originCount = (int)original.size();
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        initialize(1, 0, originCount-1, original);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int pos, T newVal) {
        update(newVal, 1, pos, 0, originCount-1);
    }
};

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    std::vector<Long> arr;
    for (int i = 0; i < n; ++i) {
        Long val;
        scanf("%lld", &val);
        arr.push_back(val);
    }
    SegTree<Long> tree(arr);

    for (int i = 0; i < m+k; ++i) {
        int kind;
        scanf("%d", &kind);

        switch (kind) {
            case 1: {
                int pos;
                Long newVal;
                scanf("%d %lld", &pos, &newVal);
                tree.update(pos-1, newVal);
                break;
            }
        
            case 2: {
                int left, right;
                scanf("%d %d", &left, &right);
                printf("%lld\n", tree.query(left-1, right-1));
                break;
            }
        }
    }

    return 0;
}