#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int datas[100001];
int tree[300001];

void Init(int node, int start, int end)
{
    if (start == end)
    {
        tree[node] = datas[start];
        return;
    }

    Init(node*2, start, (start+end)/2);
    Init(node*2+1, (start+end)/2 + 1, end);

    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

int Query(int node, int start, int end, int i, int j)
{
    if (i > end || j < start)
        return -1;

    if (i <= start && end <= j)
        return tree[node];

    int m1 = Query(2*node, start, (start+end)/2, i, j);
    int m2 = Query(2*node+1, (start+end)/2+1, end, i, j);

    if (m1 == -1)
        return m2;
    if (m2 == -1)
        return m1;
    
    return min(m1, m2);
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", &datas[i]);
    }

    Init(1, 0, N-1);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%d\n", Query(1, 0, N-1, a-1, b-1));
    }

    return 0;
}