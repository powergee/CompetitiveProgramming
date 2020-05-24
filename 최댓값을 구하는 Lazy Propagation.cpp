#include <iostream>
#include <vector>
#include <algorithm>
typedef long long Long;

Long tree[4000001];
Long lazy[4000001];

Long Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd);
void LazyUpdate(Long diff, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd);
void Propagate(int index, int start, int end);

Long Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
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

void LazyUpdate(Long diff, int dataStart, int dataEnd, int treeIndex, int treeStart, int treeEnd)
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

#define UPDATE 1
#define QUERY 2
#define EXIT 0
int main()
{
    int treeSize;
    printf("이번 테스트에 사용할 배열의 크기를 입력하십시오 :");
    scanf("%d", &treeSize);
    printf("이제부터 테스트를 시작합니다. 명령어를 입력하십시오...\n");

    while (true)
    {
        int command;
        scanf("%d", &command);

        if (command == UPDATE)
        {
            int start, end, diff;
            scanf("%d %d %d", &start, &end, &diff);
            LazyUpdate(diff, start, end, 1, 1, treeSize);
        }
        else if (command == QUERY)
        {
            int start, end;
            scanf("%d %d", &start, &end);
            printf("%lld\n", Query(1, 1, treeSize, start, end));
        }
        else if (command == EXIT)
        {
            return 0;
        }
    }

    return 0;
}