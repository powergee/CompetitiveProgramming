#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long long Long;

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> tree;

    T initialize(int index, int start, int end, const std::vector<T>& original)
    {
        if (start == end)
            return tree[index] = original[start];
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid, original);
        T right = initialize(index * 2 + 1, mid + 1, end, original);

        return tree[index] = left + right;
    }

    T query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (reqEnd < nodeStart || nodeEnd < reqStart)
            return 0;
        else if (reqStart <= nodeStart && nodeEnd <= reqEnd)
            return tree[index];
        else
        {
            T left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
            T right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
            return left + right;
        }
    }

    void update(int index, int nodeStart, int nodeEnd, int reqIndex, T newVal)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (nodeStart == nodeEnd)
            tree[index] = newVal;
        else
        {
            if (reqIndex <= nodeMid)
                update(index * 2, nodeStart, nodeMid, reqIndex, newVal);
            else
                update(index * 2 + 1, nodeMid + 1, nodeEnd, reqIndex, newVal);
            tree[index] = tree[index * 2] + tree[index * 2 + 1];
        }
    }
    
public:
    SegTree(const std::vector<T>& original)
    {
        count = (int)original.size();
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
        initialize(1, 0, count - 1, original);
    }

    T query(int start, int end)
    {
        return query(1, 0, count - 1, start, end);
    }

    void update(int index, T newVal)
    {
        update(1, 0, count - 1, index, newVal);
    }
};

int main()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    std::vector<Long> original(n);

    for (int i = 0; i < n; ++i)
        scanf("%lld", &original[i]);
    
    SegTree<Long> tree(original);
    for (int i = 0; i < m+k; ++i)
    {
        Long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);

        if (a == 1)
            tree.update(b-1, c);
        else
            printf("%lld\n", tree.query(b-1, c-1));
    }

    return 0;
}