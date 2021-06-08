#include <vector>
#include <cmath>

template<typename T>
class SegTree {
private:
    int count;
    std::vector<T> tree;

    T initialize(int index, int start, int end, const std::vector<T>& original) {
        if (start == end) {
            return tree[index] = original[start];
        }
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid, original);
        T right = initialize(index * 2 + 1, mid + 1, end, original);

        return tree[index] = (left + right);
    }

    T query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd) {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (nodeStart > reqEnd || nodeEnd < reqStart) {
            return 0;
        } else if (nodeStart >= reqStart && nodeEnd <= reqEnd) {
            return tree[index];
        } else {
            T left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
            T right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
            return left + right;
        }
    }

    void update(T value, int updatePos, int treeIndex, int treeStart, int treeEnd) {
        if (treeStart == updatePos && updatePos == treeEnd) {
            tree[treeIndex] = value;
            return;
        }

        int treeMid = (treeStart + treeEnd) / 2;
        if (updatePos <= treeMid) {
            update(value, updatePos, treeIndex * 2, treeStart, treeMid);
        } else {
            update(value, updatePos, treeIndex * 2 + 1, treeMid + 1, treeEnd);
        }
        tree[treeIndex] = tree[treeIndex * 2] + tree[treeIndex * 2 + 1];
    }
    
public:
    SegTree(const std::vector<T>& original) {
        count = (int)original.size();
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
        initialize(1, 0, count - 1, original);
    }

    SegTree(int size) {
        count = size;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
    }

    T query(int start, int end) {
        return query(1, 0, count - 1, start, end);
    }

    void update(T value, int pos) {
        update(value, pos, 1, 0, count - 1);
    }
};