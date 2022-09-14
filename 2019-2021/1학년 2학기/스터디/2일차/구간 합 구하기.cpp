#include <iostream>
#include <algorithm>
using namespace std;

typedef long long Long;

int N, M, K;
Long tree[3000001];
Long datas[1000000];

Long Init(int node, int start, int end)
{
    if (start == end)
    {
        tree[node] = datas[start];
        return datas[start];
    }

    Long left = Init(node*2, start, (start+end)/2);
    Long right = Init(node*2+1, (start+end)/2 + 1, end);

    return tree[node] = left + right;
}

void Update(int node, int start, int end, int changedIndex, Long diff)
{
    int med = (start+end)/2;

    if (start <= changedIndex && end >= changedIndex)
    {
        tree[node] += diff;
        if (start == end)
            return;
        else if (changedIndex <= med)
            Update(node*2, start, med, changedIndex, diff);
        else
            Update(node*2 + 1, med + 1, end, changedIndex, diff);
    }

    else
        return;
}

Long Sum(int node, int start, int end, int left, int right)
{
    int med = (start+end)/2;

    if (start > right || end < left)
        return 0;

    else if (start == left && right == end)
        return tree[node];

    else// if (start <= left && right <= end)
    {
        if (med >= right)
            return Sum(node * 2, start, med, left, right);

        else if (med + 1 <= left)
            return Sum(node * 2 + 1, med + 1, end, left, right);

        else
            return Sum(node * 2, start, med, left, med) + Sum(node * 2 + 1, med + 1, end, med + 1, right);
    }
}

int main()
{
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 0; i < N; ++i)
    {
        scanf("%ld", &datas[i]);
    }

    Init(1, 0, N - 1);

    for (int i = 0; i < M+K; ++i)
    {
        int a, b;
        Long c;
        scanf("%d %d %ld", &a, &b, &c);

        if (a == 1)
        {
            Update(1, 0, N - 1, b - 1, c - (Long)datas[b - 1]);
            datas[b - 1] = c;
        }
        else
        {
            printf("%ld\n", Sum(1, 0, N - 1, b-1, c-1));
        }
    }

    return 0;
}