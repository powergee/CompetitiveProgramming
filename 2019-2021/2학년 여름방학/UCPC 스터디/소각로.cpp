#include <vector>
#include <cmath>
#include <iostream>
#include <list>
#include <vector>

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> tree;

    void initialize(int index, int start, int end)
    {
        if (start == end)
        {
            tree[index] = 0;
            return;
        }
        
        int mid = (start + end) / 2;
        initialize(index * 2, start, mid);
        initialize(index * 2 + 1, mid + 1, end);

        tree[index] = -1;
    }

    void propagate(int index, int start, int end)
    {
        if (tree[index] != -1 && start != end)
        {            
            tree[index * 2] = tree[index];
            tree[index * 2 + 1] = tree[index];
            tree[index] = -1;
        }
    }

    T query(int index, int nodeStart, int nodeEnd, int request)
    {
        if (nodeStart == nodeEnd)
            return tree[index];

        propagate(index, nodeStart, nodeEnd);
        int nodeMid = (nodeStart + nodeEnd) / 2;

        if (request <= nodeMid)
            return query(index * 2, nodeStart, nodeMid, request);
        else
            return query(index * 2 + 1, nodeMid + 1, nodeEnd, request);
    }

    void update(T value, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd)
    {
        int treeMid = (treeStart + treeEnd) / 2;
        propagate(treeIndex, treeStart, treeEnd);

        if (dataEnd < treeStart || treeEnd < dataStart)
            return;
        else if (dataStart <= treeStart && treeEnd <= dataEnd)
            tree[treeIndex] = value;
        else
        {
            update(value, dataStart, dataEnd, treeIndex * 2, treeStart, treeMid);
            update(value, dataStart, dataEnd, treeIndex * 2 + 1, treeMid + 1, treeEnd);
        }
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

    T query(int request)
    {
        return query(1, 0, count - 1, request);
    }

    void update(T value, int start, int end)
    {
        update(value, start, end, 1, 0, count - 1);
    }

    void update(std::list<std::pair<int, long long>>& trashes, int start, int end)
    {
        while (start <= end && !trashes.empty())
        {
            auto current = trashes.begin();
            
            if (current->second <= (long long)(end - start + 1))
            {
                update(current->first, start, start + (int)current->second - 1);
                start += (int)current->second;
                trashes.pop_front();
            }
            else
            {
                update(current->first, start, end);
                current->second -= (end - start + 1);
                start = end+1;
            }
        }
    }
};

int main()
{
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);

    SegTree<int> tree(m);
    std::list<std::pair<int, long long>> trashes;
    int current;
    int length = 1;
    scanf("%d", &current);
    for (int i = 1; i < n; ++i)
    {
        int next;
        scanf("%d", &next);
        if (current == next)
            ++length;
        else
        {
            trashes.emplace_back(current, length);
            current = next;
            length = 1;
        }
    }
    trashes.emplace_back(current, length);
    tree.update(trashes, 0, m-1);

    while (q--)
    {
        int operation;
        scanf("%d", &operation);

        switch (operation)
        {
        case 1:
            int left, right;
            scanf("%d %d", &left, &right);
            tree.update(0, left-1, right-1);
            tree.update(trashes, left-1, right-1);
            break;

        case 2:
            int index;
            scanf("%d", &index);
            printf("%d ", tree.query(index-1));
            break;

        case 3:
            int p;
            long long q;
            scanf("%d %lld", &p, &q);
            trashes.emplace_back(p, q);
            break;

        case 4:
            long long t;
            scanf("%lld", &t);
            while (t > 0 && !trashes.empty())
            {
                if (t < trashes.begin()->second)
                {
                    trashes.begin()->second -= t;
                    t = 0;
                }
                else
                {
                    t -= trashes.begin()->second;
                    trashes.pop_front();
                }
            }
            break;
        }
    }

    printf("\n");
    for (int i = 0; i < m; ++i)
        printf("%d ", tree.query(i));

    return 0;
}