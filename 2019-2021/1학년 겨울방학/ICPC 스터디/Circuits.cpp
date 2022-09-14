#include <iostream>
#include <vector>
#include <algorithm>
typedef std::pair<int, int> Interval;

std::vector<int> indexVec;
std::vector<Interval> intervals;

int tree[4000001];
int lazy[4000001];

int Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd);
void LazyUpdate(int diff, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd);
void Propagate(int index, int start, int end);

int Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
	Propagate(index, nodeStart, nodeEnd);

	int nodeMed = (nodeStart + nodeEnd) / 2;

	if (nodeStart > reqEnd || nodeEnd < reqStart)
		return 0;

	else if (nodeStart >= reqStart && nodeEnd <= reqEnd)
		return tree[index];

	else
		return std::max(Query(index * 2, nodeStart, nodeMed, reqStart, reqEnd), Query(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd));
}

void LazyUpdate(int diff, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd)
{
	Propagate(treeIndex, treeStart, treeEnd);

	int treeMed = (treeStart + treeEnd) / 2;

	if (dataEnd < treeStart || treeEnd < dataStart)
		return;

	if (dataStart <= treeStart && treeEnd <= dataEnd)
	{
		tree[treeIndex] += diff;
		if (treeStart != treeEnd)
		{
			lazy[treeIndex * 2] += diff;
			lazy[treeIndex * 2 + 1] += diff;
		}
		return;
	}

	LazyUpdate(diff, dataStart, dataEnd, treeIndex * 2, treeStart, treeMed);
	LazyUpdate(diff, dataStart, dataEnd, treeIndex * 2 + 1, treeMed + 1, treeEnd);

	tree[treeIndex] = std::max(tree[treeIndex * 2], tree[treeIndex * 2 + 1]);
}

void Propagate(int index, int start, int end)
{
	if (lazy[index] != 0)
	{
		tree[index] += lazy[index];

		if (start != end)
		{
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}

		lazy[index] = 0;
	}
}

int GetIndex(int y)
{
    return std::lower_bound(indexVec.begin(), indexVec.end(), y) - indexVec.begin();
}

bool IsOnInterval(int smallPos, Interval& it)
{
    int smallY1 = GetIndex(it.first);
    int smallY2 = GetIndex(it.second);
    return smallY1 <= smallPos && smallPos <= smallY2;
}

void UpdateIndex(int& firstPos, int& itIndex1, int& itIndex2)
{
    ++firstPos;

    while (!IsOnInterval(firstPos, intervals[itIndex1]))
        ++itIndex1;

    while (IsOnInterval(firstPos, intervals[itIndex2]))
        ++itIndex2;
    --itIndex2;
}

int main()
{
    int n;
    scanf("%d", &n);

    int t1, t2;
    for (int i = 0; i < n; ++i)
    {
        int bottom, top;
        scanf("%d %d %d %d", &t1, &bottom, &t2, &top);
        indexVec.push_back(bottom);
        indexVec.push_back(top);
        intervals.push_back({bottom, top});
    }

    std::sort(indexVec.begin(), indexVec.end());
    indexVec.erase(std::unique(indexVec.begin(), indexVec.end()), indexVec.end());

    for (Interval& it : intervals)
    {
        int smallY1 = GetIndex(it.first);
        int smallY2 = GetIndex(it.second);
        LazyUpdate(1, smallY1, smallY2, 1, 1, n);
    }

    int firstPos = 0;
    int itIndex1 = 0, itIndex2 = 0;
    UpdateIndex(firstPos, itIndex1, itIndex2);
    for (int i = itIndex1; i <= itIndex2; ++i)
        LazyUpdate(-1, GetIndex(intervals[i].first), GetIndex(intervals[i].second), 1, 1, n);
    
    int answer = -1;
    while (true)
    {
        answer = std::max(answer, (itIndex2 - itIndex1 + 1) + Query(1, 1, n, 1, n));
        
        int prevIndex2 = itIndex2;
        UpdateIndex(firstPos, itIndex1, itIndex2);

        for (int i = prevIndex2 + 1; i <= itIndex2; ++i)
            LazyUpdate(-1, GetIndex(intervals[i].first), GetIndex(intervals[i].second), 1, 1, n);
    }

    printf("%d", answer);

    return 0;
}