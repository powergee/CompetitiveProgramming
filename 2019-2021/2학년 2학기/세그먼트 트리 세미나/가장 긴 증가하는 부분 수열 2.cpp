#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> nodes;

    T initialize(int index, int start, int end, const std::vector<T>& original)
    {
        if (start == end)
            return nodes[index] = original[start];
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid, original);
        T right = initialize(index * 2 + 1, mid + 1, end, original);

        return nodes[index] = std::max(left, right);
    }

    T query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (reqEnd < nodeStart || nodeEnd < reqStart)
            return 0;
        else if (reqStart <= nodeStart && nodeEnd <= reqEnd)
            return nodes[index];
        else
        {
            T left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
            T right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
            return std::max(left, right);
        }
    }

    void update(int index, int nodeStart, int nodeEnd, int reqIndex, T newVal)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (nodeStart == nodeEnd)
            nodes[index] = newVal;
        else
        {
            if (reqIndex <= nodeMid)
                update(index * 2, nodeStart, nodeMid, reqIndex, newVal);
            else
                update(index * 2 + 1, nodeMid + 1, nodeEnd, reqIndex, newVal);
            nodes[index] = std::max(nodes[index * 2], nodes[index * 2 + 1]);
        }
    }
    
public:
    SegTree(int size)
    {
        count = size;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        nodes.resize(vecSize, 0);
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
    int n;
    scanf("%d", &n);

    std::vector<std::pair<int, int>> valIdxPairs(n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &valIdxPairs[i].first);
        valIdxPairs[i].second = i;
    }

    SegTree<int> tree(n);
    std::sort(valIdxPairs.begin(), valIdxPairs.end(), [](auto p1, auto p2) -> bool {
        if (p1.first == p2.first)
            return p1.second > p2.second;
        else return p1.first < p2.first;
    });
    int answer = 0;

    for (int i = 0; i < n; ++i)
    {
        int current = 0;

        if (valIdxPairs[i].second == 0)
            current = 1;
        else
            current = 1 + tree.query(0, valIdxPairs[i].second-1);
        
        tree.update(valIdxPairs[i].second, current);
        answer = std::max(answer, current);
    }

    printf("%d", answer);
}