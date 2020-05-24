#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int datas[100001];
int treeMin[300001];
int treeMax[300001];

void InitMin(int node, int start, int end)
{
    if (start == end)
    {
        treeMin[node] = datas[start];
        return;
    }

    InitMin(node*2, start, (start+end)/2);
    InitMin(node*2+1, (start+end)/2 + 1, end);

    treeMin[node] = min(treeMin[node * 2], treeMin[node * 2 + 1]);
}

int QueryMin(int node, int start, int end, int i, int j)
{
    if (i > end || j < start)
        return -1;

    if (i <= start && end <= j)
        return treeMin[node];

    int m1 = QueryMin(2*node, start, (start+end)/2, i, j);
    int m2 = QueryMin(2*node+1, (start+end)/2+1, end, i, j);

    if (m1 == -1)
        return m2;
    if (m2 == -1)
        return m1;
    
    return min(m1, m2);
}

void InitMax(int node, int start, int end)
{
    if (start == end)
    {
        treeMax[node] = datas[start];
        return;
    }

    InitMax(node*2, start, (start+end)/2);
    InitMax(node*2+1, (start+end)/2 + 1, end);

    treeMax[node] = max(treeMax[node * 2], treeMax[node * 2 + 1]);
}

int QueryMax(int node, int start, int end, int i, int j)
{
    if (i > end || j < start)
        return -1;

    if (i <= start && end <= j)
        return treeMax[node];

    int m1 = QueryMax(2*node, start, (start+end)/2, i, j);
    int m2 = QueryMax(2*node+1, (start+end)/2+1, end, i, j);

    if (m1 == -1)
        return m2;
    if (m2 == -1)
        return m1;
    
    return max(m1, m2);
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &datas[i]);
    }

    InitMin(1, 0, N-1);
    InitMax(1, 0, N-1);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%d ", QueryMin(1, 0, N-1, a-1, b-1));
        printf("%d\n", QueryMax(1, 0, N-1, a-1, b-1));
    }

    return 0;
}