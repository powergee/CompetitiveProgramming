#include <iostream>
#include <algorithm>
#define INVALID_MIN 0x7fffffff
#define INVALID_MAX -0x80000000

int nums[100001];
int treeMax[300001];
int treeMin[300001];

void Init(int node, int start, int end)
{
    if (start == end)
    {
        treeMin[node] = nums[start];
        treeMax[node] = nums[start];

        return;
    }

    Init(node * 2, start, (start + end) / 2);
    Init(node * 2 + 1, (start + end) / 2 + 1, end);

    treeMin[node] = std::min(treeMin[node * 2], treeMin[node * 2 + 1]);
    treeMax[node] = std::max(treeMax[node * 2], treeMax[node * 2 + 1]);
}

int QueryMin(int node, int start, int end, int i, int j)
{
    if (i > end || j < start)
        return INVALID_MIN;

    if (i <= start && end <= j)
        return treeMin[node];

    int m1 = QueryMin(node * 2, start, (start + end) / 2, i, j);
    int m2 = QueryMin(node * 2 + 1, (start + end) / 2 + 1, end, i , j);
    
    return std::min(m1, m2);
}

int QueryMax(int node, int start, int end, int i, int j)
{
    if (i > end || j < start)
        return INVALID_MAX;

    if (i <= start && end <= j)
        return treeMax[node];

    int m1 = QueryMax(node * 2, start, (start + end) / 2, i, j);
    int m2 = QueryMax(node * 2 + 1, (start + end) / 2 + 1, end, i, j);

    return std::max(m1, m2);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &nums[i]);
    }

    Init(1, 0, N-1);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%d %d\n", QueryMin(1, 0, N-1, a-1, b-1), QueryMax(1, 0, N-1, a-1, b-1));
    }

    return 0;
}