#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template<typename T>
class SegTree
{
private:
    int count;
    std::vector<T> tree;
    std::vector<T> lazy;

    T initialize(int index, int start, int end, const std::vector<T>& original)
    {
        if (start == end)
            return tree[index] = original[start];
        
        int mid = (start + end) / 2;
        T left = initialize(index * 2, start, mid, original);
        T right = initialize(index * 2 + 1, mid + 1, end, original);

        return tree[index] = std::max(left, right);
    }

    void propagate(int index, int start, int end)
    {
        if (lazy[index] != 0)
        {
            tree[index] += lazy[index] * (end - start + 1);

            if (start != end)
            {
                lazy[index * 2] += lazy[index];
                lazy[index * 2 + 1] += lazy[index];
            }

            lazy[index] = 0;
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
            return std::max(left, right);
        }
    }

    void update(T add, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd)
    {
        propagate(treeIndex, treeStart, treeEnd);

        int treeMid = (treeStart + treeEnd) / 2;

        if (dataEnd < treeStart || treeEnd < dataStart)
            return;
        
        if (dataStart <= treeStart && treeEnd <= dataEnd)
        {
            tree[treeIndex] += add;
            if (treeStart != treeEnd)
            {
                lazy[treeIndex * 2] += add;
                lazy[treeIndex * 2 + 1] += add;
            }
            return;
        }

        update(add, dataStart, dataEnd, treeIndex * 2, treeStart, treeMid);
        update(add, dataStart, dataEnd, treeIndex * 2 + 1, treeMid + 1, treeEnd);

        tree[treeIndex] = std::max(tree[treeIndex * 2], tree[treeIndex * 2 + 1]);
    }
    
public:
    SegTree(const std::vector<T>& original)
    {
        count = (int)original.size();
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
        initialize(1, 0, count - 1, original);
    }

    SegTree(int size)
    {
        count = size;
        int treeHeight = (int)ceil(log2(count));
        int vecSize = (1 << (treeHeight + 1));
        tree.resize(vecSize);
        lazy.resize(vecSize);
    }

    T query(int start, int end)
    {
        return query(1, 0, count - 1, start, end);
    }

    void update(T add, int start, int end)
    {
        update(add, start, end, 1, 0, count - 1);
    }
};

bool compareContest(const std::pair<int, int>& c1, const std::pair<int, int> c2)
{
    if (c1.second != c2.second)
        return c1.second < c2.second;
    return c1.first < c2.first;
}

bool haveIntersection(std::pair<int, int>& p1, std::pair<int, int>& p2)
{
    return  (p1.first <= p2.first && p2.first <= p1.second) || 
            (p1.first <= p2.second && p2.second <= p1.second) ||
            (p2.first <= p1.first && p1.first <= p2.second) || 
            (p2.first <= p1.second && p1.second <= p2.second);
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<std::pair<int, int>> contests;
    std::vector<int> positions;
    for (int i = 0; i < n; ++i)
    {
        int s, e;
        scanf("%d %d", &s, &e);
        contests.emplace_back(s, e);
        positions.push_back(s);
        positions.push_back(e);
    }

    std::sort(positions.begin(), positions.end());
    positions.erase(std::unique(positions.begin(), positions.end()), positions.end());
    for (int i = 0; i < n; ++i)
    {
        contests[i].first = std::lower_bound(positions.begin(), positions.end(), contests[i].first) - positions.begin();
        contests[i].second = std::lower_bound(positions.begin(), positions.end(), contests[i].second) - positions.begin();
    }
    std::sort(contests.begin(), contests.end(), compareContest);

    int posCount = positions.size();
    SegTree<int> tree(posCount);
    int answer = 0;
    std::pair<int, int> lastParticipated = {-1, -1};
    for (int i = 0; i < n; ++i)
    {
        if (haveIntersection(lastParticipated, contests[i]))
            continue;

        if (tree.query(contests[i].first, contests[i].second) < k-1)
            tree.update(1, contests[i].first, contests[i].second);
        else
        {
            ++answer;
            lastParticipated = contests[i];
        }
    }

    printf("%d", answer);

    return 0;
}