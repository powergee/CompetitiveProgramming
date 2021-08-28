#include <iostream>
#include <algorithm>

#include <vector>
#include <cmath>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;
    std::vector<T> lazy;

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
            return std::min(query(index*2, reqStart, reqEnd, treeStart, treeMed),
                            query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd));
        } else {
            return __INT32_MAX__;
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
            tree[index] = std::min(tree[index*2], tree[index*2+1]);
        }
    }

public:
    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize, 0);
        lazy.resize(vecSize, 0);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int start, int end, T add) {
        update(add, 1, start, end, 0, originCount-1);
    }

    void print() {
        for (int p = 1; p < originCount; ++p) {
            printf("%d ", query(p, p));
        }
        printf("\n");
    }
};

struct Line {
    int l, r, w;

    Line(int pl, int pr, int pw) {
        l = pl;
        r = pr;
        w = pw;
    }

    Line() : Line(0, 0, 0) {}
};

Line lines[300000];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        int l, r, w;
        scanf("%d %d %d", &l, &r, &w);
        lines[i] = Line(l, r, w);
    }

    std::sort(lines, lines+n, [](Line l1, Line l2) -> bool {
        return l1.w < l2.w;
    });
    SegTree<int> segUnion(m+1);

    int j = 1;
    int answer = __INT32_MAX__;
    segUnion.update(lines[0].l, lines[0].r-1, 1);
    for (int i = 0; i < n; ++i) {
        while (j < n && segUnion.query(1, m-1) == 0) {
            segUnion.update(lines[j].l, lines[j].r-1, 1);
            ++j;
        }
        if (segUnion.query(1, m-1) == 0) {
            break;
        }
        answer = std::min(answer, lines[j-1].w - lines[i].w);
        segUnion.update(lines[i].l, lines[i].r-1, -1);
    }

    printf("%d", answer);

    return 0;
}