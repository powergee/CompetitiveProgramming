#include <vector>
#include <cmath>
#include <iostream>

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> nodes;

    T query(int index, int nodeStart, int nodeEnd, int nTh)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (nodeStart == nodeEnd)
            return nodeStart;
        if (nTh <= nodes[index*2])
            return query(index*2, nodeStart, nodeMid, nTh);
        else
            return query(index*2+1, nodeMid+1, nodeEnd, nTh - nodes[index*2]);
    }

    void update(int index, int nodeStart, int nodeEnd, int reqIndex, T add)
    {
        int nodeMid = (nodeStart + nodeEnd) / 2;
        nodes[index] += add;

        if (nodeStart == nodeEnd)
            return;
        if (reqIndex <= nodeMid)
            update(index * 2, nodeStart, nodeMid, reqIndex, add);
        else 
            update(index * 2 + 1, nodeMid + 1, nodeEnd, reqIndex, add);
    }
    
public:
    SegTree(int size)
    {
        count = size;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        nodes.resize(vecSize);
    }

    T getValue(int nTh)
    {
        return query(1, 0, count - 1, nTh);
    }

    void update(int index, T add)
    {
        update(1, 0, count - 1, index, add);
    }
};

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    std::vector<int> history(n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &history[i]);
    
    SegTree<int> tempTree(65537);
    for (int i = 0; i < k; ++i)
        tempTree.update(history[i], 1);
    
    long long answer = 0;
    for (int i = k; i < n; ++i)
    {
        answer += tempTree.getValue((k+1)/2);
        tempTree.update(history[i-k], -1);
        tempTree.update(history[i], 1);
    }
    answer += tempTree.getValue((k+1)/2);

    printf("%lld", answer);

    return 0;
}