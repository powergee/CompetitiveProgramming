#include <iostream>
#include <vector>
#include <cmath>

using Long = long long;

template <typename T>
class SegTree {
private:
    int originCount;
    std::vector<T> tree;

    T query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
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

    void update(T add, int index, int reqPos, int treeStart, int treeEnd) {
        if (treeStart == reqPos && treeEnd == reqPos) {
            tree[index] += add;
        } else if (treeStart <= reqPos && reqPos <= treeEnd) {
            int treeMed = (treeStart + treeEnd) / 2;
            update(add, index*2, reqPos, treeStart, treeMed);
            update(add, index*2+1, reqPos, treeMed+1, treeEnd);
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

public:
    SegTree(int count) {
        originCount = count;
        int treeHeight = (int)std::ceil((float)std::log2(originCount));
        int vecSize = (1 << (treeHeight+1));
        tree.resize(vecSize);
    }

    T query(int start, int end) {
        return query(1, start, end, 0, originCount-1);
    }

    void update(int pos, T add) {
        update(add, 1, pos, 0, originCount-1);
    }
};

int main() {
    int n;
    scanf("%d", &n);

    SegTree<int> tree(n+1);
    std::vector<int> answer(n+1, 0);

    for (int i = 1; i <= n; ++i) {
        int count;
        scanf("%d", &count);

        int left = 1, right = n+1;
        while (left < right) {
            int mid = (left+right)/2;
            int bigger = std::max(0, mid-1) - tree.query(1, mid-1);

            if (bigger < count) {
                left = mid+1;
            } else if (bigger == count) {
                if (left == mid) {
                    break;
                } else {
                    left = mid;
                }
            } else {
                right = mid-1;
            }
        }

        int pos = (answer[left] > 0 ? left+1 : left);
        answer[pos] = i;
        tree.update(pos, 1);
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d\n", answer[i]);
    }

    return 0;
}