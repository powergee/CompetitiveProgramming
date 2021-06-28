#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using Long = long long;

class SegTree {
private:
    int originCount;
    std::vector<Long> tree;
    std::vector<int> count;

    void initialize(int index, int start, int end, const std::vector<Long>& original) {
        if (start == end) {
            tree[index] = original[start];
        } else {
            int mid = (start + end) / 2;
            initialize(index * 2, start, mid, original);
            initialize(index * 2 + 1, mid + 1, end, original);
        }
    }

    void propagate(int index, int start, int end) {
        if (count[index] != 0 && start < end) {
            int med = (start + end) / 2;
            tree[index*2] += tree[index];
            count[index*2] += count[index];
            tree[index*2+1] += tree[index]+((med-start+1)*count[index]);
            count[index*2+1] += count[index];

            tree[index] = count[index] = 0;
        }
    }

    Long query(int index, int req, int treeStart, int treeEnd) {
        if (treeStart == treeEnd) {
            return tree[index];
        }

        propagate(index, treeStart, treeEnd);
        int treeMed = (treeStart + treeEnd) / 2;

        if (req <= treeMed) {
            return query(index*2, req, treeStart, treeMed);
        } else {
            return query(index*2+1, req, treeMed+1, treeEnd);
        }
    }

    void update(int index, int addStart, int addEnd, int treeStart, int treeEnd) {
        if (addStart <= treeStart && treeEnd <= addEnd) {
            tree[index] += treeStart - addStart + 1;
            count[index]++;
        } else if (treeStart <= addEnd && addStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(index*2, addStart, addEnd, treeStart, treeMed);
            update(index*2+1, addStart, addEnd, treeMed+1, treeEnd);
        }
    }
    
public:
    SegTree(const std::vector<Long>& original) {
        originCount = (int)original.size();
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
        count.resize(vecSize);
        initialize(1, 0, originCount-1, original);
    }

    Long query(int pos) {
        return query(1, pos, 0, originCount-1);
    }

    void update(int start, int end) {
        update(1, start, end, 0, originCount-1);
    }
};

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    SegTree tree(arr);

    int q;
    scanf("%d", &q);
    while (q--) {
        int kind;
        scanf("%d", &kind);

        switch (kind)
        {
        case 1:
            int left, right;
            scanf("%d %d", &left, &right);
            tree.update(left-1, right-1);
            break;
        
        case 2:
            int pos;
            scanf("%d", &pos);
            printf("%lld\n", tree.query(pos-1));
            break;
        }
    }
}