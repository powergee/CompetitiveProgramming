#include <iostream>
typedef long long Long;

Long nums[1000001];
Long tree[4000001];

Long Init(int treeIndex, int start, int end)
{
    if (start == end)
        return tree[treeIndex] = nums[start];

    Long r1 = Init(treeIndex * 2, start, (start + end) / 2);
    Long r2 = Init(treeIndex * 2 + 1, (start + end) / 2 + 1, end);

    return tree[treeIndex] = r1 + r2;
}

Long Query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
    int nodeMed = (nodeStart + nodeEnd) / 2;

    if (nodeStart > reqEnd || nodeEnd < reqStart)
        return 0;

    else if (nodeStart >= reqStart && nodeEnd <= reqEnd)
        return tree[index];

    else
        return Query(index * 2, nodeStart, nodeMed, reqStart, reqEnd) + Query(index * 2 + 1, nodeMed + 1, nodeEnd, reqStart, reqEnd);
}

void Update(int diff, int dataIndex, int treeIndex, int start, int end)
{
    int med = (start + end) / 2;

    if (start > dataIndex || end < dataIndex)
        return;

    tree[treeIndex] += diff;
    if (start == end)
        return;

    else if (dataIndex <= med)
        Update(diff, dataIndex, treeIndex * 2, start, med);
    else
        Update(diff, dataIndex, treeIndex * 2 + 1, med + 1, end);
}

int main()
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 1; i <= N; ++i)
        scanf("%lld", &nums[i]);

    Init(1, 1, N);
    
    for (int i = 0; i < M + K; ++i)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        switch (a)
        {
        case 1:
            Update(c - nums[b], b, 1, 1, N);
            nums[b] = c;
            break;
        case 2:
            printf("%lld\n", Query(1, 1, N, b, c));
            break;
        }
    }

    return 0;
}