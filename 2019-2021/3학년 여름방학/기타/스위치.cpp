#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

class SegTree {
private:
    int originCount;
    std::vector<int> tree;
    std::vector<bool> inversed;
    
    void propagate(int index, int start, int end) {
        if (inversed[index]) {
            tree[index] = (end-start+1) - tree[index];
            inversed[index] = false;
            if (start < end) {
                inversed[index*2] = !inversed[index*2];
                inversed[index*2+1] = !inversed[index*2+1];
            }
        }
    }

    int query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            return tree[index];
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            return query(index*2, reqStart, reqEnd, treeStart, treeMed)
                 + query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
        } else {
            return 0;
        }
    }

    void inverse(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
        propagate(index, treeStart, treeEnd);

        if (reqStart <= treeStart && treeEnd <= reqEnd) {
            inversed[index] = !inversed[index];
            propagate(index, treeStart, treeEnd);
        } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            inverse(index*2, reqStart, reqEnd, treeStart, treeMed);
            inverse(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

public:
    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize, 0);
        inversed.resize(vecSize, false);
    }

    int query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void inverse(int start, int end) {
        inverse(1, start, end, 0, originCount-1);
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    auto tree = SegTree(n);
    while (m--) {
        int com, x, y;
        scanf("%d %d %d", &com, &x, &y);

        switch (com)
        {
        case 0:
            tree.inverse(x-1, y-1);
            break;
        
        case 1:
            printf("%d\n", tree.query(x-1, y-1));
            break;
        }
    }
    
    return 0;
}