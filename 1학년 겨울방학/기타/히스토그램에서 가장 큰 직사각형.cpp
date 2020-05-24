#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

typedef long long Long;

std::vector<int> histo;
// 세그먼트 트리 (min)
std::vector<std::pair<int, int>> tree;
int n;

std::pair<int, int> Init(int treeIndex, int start, int end)
{
    if (start == end)
        return tree[treeIndex] = { histo[start], start };

    std::pair<int, int> l = Init(treeIndex * 2, start, (start + end) / 2);
    std::pair<int, int> r = Init(treeIndex * 2 + 1, (start + end) / 2 + 1, end);

    return tree[treeIndex] = std::min(l, r);
}

std::pair<int, int> Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
    int nodeMed = (nodeStart + nodeEnd) / 2;

    if (reqEnd < nodeStart || nodeEnd < reqStart)
        return { INT32_MAX, 0 };

    else if (reqStart <= nodeStart && nodeEnd <= reqEnd)
        return tree[index];

    else return std::min(Query(index * 2, nodeStart, nodeMed, reqStart, reqEnd), Query(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd));
}

Long FindAnswer(int start, int end)
{
    if (start == end)
        return histo[start];
    else if (end < start)
        return 0;

    std::pair<int, int> min = Query(1, 1, n, start, end);

    Long now = (Long)min.first * (end - start + 1);
    return std::max(now, std::max(FindAnswer(start, min.second - 1), FindAnswer(min.second + 1, end)));
}

int main()
{
    while (true)
    {
        histo.clear();
        tree.clear();

        scanf("%d", &n);

        if (n == 0)
            break;

        tree.resize(4 * n + 1);
        histo.resize(n + 1);

        for (int i = 1; i <= n; ++i)
            scanf("%d", &histo[i]);

        Init(1, 1, n);
        printf("%lld\n", FindAnswer(1, n));
    }

    return 0;
}