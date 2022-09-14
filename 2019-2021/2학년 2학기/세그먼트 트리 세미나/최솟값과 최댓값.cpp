#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <climits>

typedef long long Long;

template<typename T, class Comp>
class SegTree
{
private:
    int count;
    std::vector<T> nodes;
    Comp compare;
    T base;

    T initialize(int index, int start, int end, const std::vector<T>& original)
    {
        if (start == end)
            return nodes[index] = original[start];
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid, original);
        T right = initialize(index * 2 + 1, mid + 1, end, original);

        return nodes[index] = (compare(left, right) ? left : right);
    }

    T query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (reqEnd < nodeStart || nodeEnd < reqStart)
            return base;
        else if (reqStart <= nodeStart && nodeEnd <= reqEnd)
            return nodes[index];
        else
        {
            T left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
            T right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
            return compare(left, right) ? left : right;
        }
    }
    
public:
    SegTree(const std::vector<T>& original, T base)
    {
        count = (int)original.size();
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        nodes.resize(vecSize);
        this->base = base;
        initialize(1, 0, count - 1, original);
    }

    T query(int start, int end)
    {
        return query(1, 0, count - 1, start, end);
    }
};

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    std::vector<int> original(n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &original[i]);
    
    SegTree<int, std::less<int>> smaller(original, INT32_MAX);
    SegTree<int, std::greater<int>> bigger(original, INT32_MIN);

    while (m--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d %d\n", smaller.query(a-1, b-1), bigger.query(a-1, b-1));
    }
}