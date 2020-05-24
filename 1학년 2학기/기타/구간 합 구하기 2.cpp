#include <iostream>

typedef long long Long;

Long nums[1000001];
Long tree[4000001];
Long lazy[4000001];

Long Init(int index, int start, int end);
Long Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd);
void LazyUpdate(Long diff, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd);
void Propagate(int index, int start, int end);

Long Init(int index, int start, int end)
{
	if (start == end)
		return tree[index] = nums[start];

	int med = (start + end) / 2;
	Long left = Init(index * 2, start, med);
	Long right = Init(index * 2 + 1, med + 1, end);

	return tree[index] = left + right;
}

Long Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
	Propagate(index, nodeStart, nodeEnd);

	int nodeMed = (nodeStart + nodeEnd) / 2;

	if (nodeStart > reqEnd || nodeEnd < reqStart)
		return 0;

	else if (nodeStart >= reqStart && nodeEnd <= reqEnd)
		return tree[index];

	else
		return Query(index * 2, nodeStart, nodeMed, reqStart, reqEnd) + Query(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd);
}

void LazyUpdate(Long diff, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd)
{
	Propagate(treeIndex, treeStart, treeEnd);

	int treeMed = (treeStart + treeEnd) / 2;

	if (dataEnd < treeStart || treeEnd < dataStart)
		return;

	if (dataStart <= treeStart && treeEnd <= dataEnd)
	{
		tree[treeIndex] += diff * ((Long)treeEnd - treeStart + 1);
		if (treeStart != treeEnd)
		{
			lazy[treeIndex * 2] += diff;
			lazy[treeIndex * 2 + 1] += diff;
		}
		return;
	}

	LazyUpdate(diff, dataStart, dataEnd, treeIndex * 2, treeStart, treeMed);
	LazyUpdate(diff, dataStart, dataEnd, treeIndex * 2 + 1, treeMed + 1, treeEnd);

	tree[treeIndex] = tree[treeIndex * 2] + tree[treeIndex * 2 + 1];
}

void Propagate(int index, int start, int end)
{
	if (lazy[index] != 0)
	{
		tree[index] += lazy[index] * ((Long)end - start + 1);

		if (start != end)
		{
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}

		lazy[index] = 0;
	}
}

int main()
{
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);

	for (int i = 1; i <= N; ++i)
		scanf("%lld", nums + i);

	Init(1, 1, N);

	for (int i = 0; i < M + K; ++i)
	{
		int com;
		scanf("%d", &com);

		int from, to;
		switch (com)
		{
		case 1:
			Long add;
			scanf("%d %d %lld", &from, &to, &add);
			LazyUpdate(add, from, to, 1, 1, N);
			break;
		case 2:
			scanf("%d %d", &from, &to);
			printf("%lld\n", Query(1, 1, N, from, to));
			break;
		}
	}

	return 0;
}