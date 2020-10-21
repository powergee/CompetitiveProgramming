#include <iostream>
#include <vector>
#include <cmath>

#define MAKE_ONE 1
#define MAKE_ZERO 0
#define DEFAULT -1

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> tree;
    std::vector<T> lazy;

    T initialize(int index, int start, int end)
    {
        if (start == end)
            return tree[index] = 1;
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid);
        T right = initialize(index * 2 + 1, mid + 1, end);

        return tree[index] = (left + right);
    }

    void propagate(int index, int start, int end)
    {
        if (lazy[index] != DEFAULT)
        {
            tree[index] = lazy[index] * (end - start + 1);

            if (start != end)
            {
                lazy[index * 2] = lazy[index];
                lazy[index * 2 + 1] = lazy[index];
            }

            lazy[index] = DEFAULT;
        }
    }

    T query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
    {
        propagate(index, nodeStart, nodeEnd);

        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (nodeStart > reqEnd || nodeEnd < reqStart)
            return 0;

        else if (nodeStart >= reqStart && nodeEnd <= reqEnd)
            return tree[index];
        
        else
        {
            T left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
            T right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
            return left + right;
        }
    }

    void update(T newVal, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd)
    {
        propagate(treeIndex, treeStart, treeEnd);

        int treeMid = (treeStart + treeEnd) / 2;

        if (dataEnd < treeStart || treeEnd < dataStart)
            return;
        
        if (dataStart <= treeStart && treeEnd <= dataEnd && newVal != DEFAULT)
        {
            tree[treeIndex] = newVal * (treeEnd - treeStart + 1);
            if (treeStart != treeEnd)
            {
                lazy[treeIndex * 2] = newVal;
                lazy[treeIndex * 2 + 1] = newVal;
            }
            return;
        }

        update(newVal, dataStart, dataEnd, treeIndex * 2, treeStart, treeMid);
        update(newVal, dataStart, dataEnd, treeIndex * 2 + 1, treeMid + 1, treeEnd);

        tree[treeIndex] = tree[treeIndex * 2] + tree[treeIndex * 2 + 1];
    }
    
public:
    SegTree(int n)
    {
        count = n;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
        lazy.resize(vecSize, DEFAULT);
        initialize(1, 0, count - 1);
    }

    T query(int start, int end)
    {
        return query(1, 0, count - 1, start, end);
    }

    void update(T newVal, int start, int end)
    {
        update(newVal, start, end, 1, 0, count - 1);
    }
};

int n;
std::vector<int> children[100000];
std::vector<int> nodes;
std::pair<int, int> intervals[100000];

int labelNode(int start, int currIdx)
{
    nodes[currIdx] = start;

    int endIdx = currIdx;
    for (int child : children[start])
        endIdx = labelNode(child, endIdx + 1);

    intervals[start] = {currIdx, endIdx};
    return endIdx;
}

int main()
{
    scanf("%d", &n);
    nodes.resize(n);
    
    int root;
    for (int i = 0; i < n; ++i)
    {
        int upper;
        scanf("%d", &upper);
        if (upper == 0)
            root = i;
        else
            children[upper-1].push_back(i);
    }

    labelNode(root, 0);
    SegTree<int> tree(n);
    int q;
    scanf("%d", &q);

    while (q--)
    {
        int com, num;
        scanf("%d %d", &com, &num);
        std::pair<int, int> interval = intervals[--num];

        switch (com)
        {
        case 1:
            if (interval.second - interval.first)
                tree.update(MAKE_ONE, interval.first+1, interval.second);
            break;

        case 2:
            if (interval.second - interval.first)
                tree.update(MAKE_ZERO, interval.first+1, interval.second);
            break;

        case 3:
            if (interval.second - interval.first)
                printf("%d\n", tree.query(interval.first+1, interval.second));
            else printf("0\n");
            break;
        }
    }

    return 0;
}