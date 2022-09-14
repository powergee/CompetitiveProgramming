#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long Long;

struct Node
{
    Long sum, max;
};

class SegTree
{
private:
    int count;
    std::vector<Node> tree;

    void initialize(int index, int start, int end)
    {
        if (start == end)
        {
            tree[index] = {0, start};
            return;
        }
        
        int mid = (start + end) / 2;
        initialize(index * 2, start, mid);
        initialize(index * 2 + 1, mid + 1, end);

        tree[index].sum = tree[index*2].sum + tree[index*2+1].sum;
        tree[index].max = std::max(tree[index*2+1].max, tree[index*2].max + tree[index*2+1].sum);
    }

    void query(int currNode, int indexToFind, int indexStart, int indexEnd, Long& result)
    {
        if (indexEnd <= indexToFind)
        {
            result = std::max(tree[currNode].max, result + tree[currNode].sum);
            return;
        }

        int indexMid = (indexStart+indexEnd)/2;
        query(currNode*2, indexToFind, indexStart, indexMid, result);
        if (indexMid < indexToFind)
            query(currNode*2+1, indexToFind, indexMid+1, indexEnd, result);
    }

    void update(int currNode, int indexStart, int indexEnd, int indexToFind, Long value)
    {
        if (indexStart == indexEnd)
        {
            tree[currNode].sum += value;
            tree[currNode].max += value;
            return;
        }

        int indexMid = (indexStart+indexEnd)/2;
        if (indexToFind <= indexMid)
            update(currNode*2, indexStart, indexMid, indexToFind, value);
        else update(currNode*2+1, indexMid+1, indexEnd, indexToFind, value);

        tree[currNode].sum = tree[currNode*2].sum + tree[currNode*2+1].sum;
        tree[currNode].max = std::max(tree[currNode*2+1].max, tree[currNode*2].max + tree[currNode*2+1].sum);
    }
    
public:
    SegTree(int size)
    {
        count = size;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
        initialize(1, 0, count - 1);
    }

    Long query(int index)
    {
        Long result = 0;
        query(1, index, 0, count-1, result);
        return result;
    }

    void update(Long value, int index)
    {
        return update(1, 0, count-1, index, value);
    }
};

int main()
{
    int q;
    scanf("%d", &q);

    SegTree tree(1000000);
    std::vector<std::pair<int, int>> res(q+1);

    for (int id = 1; id <= q; ++id)
    {
        char com[2];
        int t, d, i;
        scanf("%s", com);
        
        switch (com[0])
        {
        case '+':
            scanf("%d %d", &t, &d);
            res[id] = {t, d};
            tree.update(d, t);
            break;

        case '-':
            scanf("%d", &i);
            tree.update(-res[i].second, res[i].first);
            break;

        case '?':
            scanf("%d", &t);
            printf("%lld\n", std::max(0LL, tree.query(t)-t));
            break;
        }
    }
}