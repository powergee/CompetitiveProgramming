#include <iostream>
#define ARRAY_SIZE 1000000

typedef long long Base;

Base original[ARRAY_SIZE];
Base nodes[ARRAY_SIZE * 4];
int n, m, k;

Base initialize(int index, int start, int end)
{
    if (start == end)
        return nodes[index] = original[start];
    
    int mid = (start + end) / 2;
    Base left = initialize(index * 2, start, mid);
    Base right = initialize(index * 2 + 1, mid + 1, end);

    return nodes[index] = left + right;
}

Base query(int index, int nodeStart, int nodeEnd, int reqStart, int reqEnd)
{
    int nodeMid = (nodeStart + nodeEnd) / 2;

    if (reqEnd < nodeStart || nodeEnd < reqStart)
        return 0;
    else if (reqStart <= nodeStart && nodeEnd <= reqEnd)
        return nodes[index];
    else
    {
        Base left = query(index * 2, nodeStart, nodeMid, reqStart, reqEnd);
        Base right = query(index * 2 + 1, nodeMid + 1, nodeEnd, reqStart, reqEnd);
        return left + right;
    }
}

void update(int index, int nodeStart, int nodeEnd, int reqIndex, Base newVal)
{
    int nodeMid = (nodeStart + nodeEnd) / 2;

    if (nodeStart == nodeEnd)
        nodes[index] = newVal;
    else
    {
        if (reqIndex <= nodeMid)
            update(index * 2, nodeStart, nodeMid, reqIndex, newVal);
        else
            update(index * 2 + 1, nodeMid + 1, nodeEnd, reqIndex, newVal);
        nodes[index] = nodes[index * 2] + nodes[index * 2 + 1];
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; ++i)
        scanf("%lld", original + i);
    
    initialize(1, 0, n-1);
    for (int i = 0; i < m+k; ++i)
    {
        Base a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);

        if (a == 1)
            update(1, 0, n-1, b-1, c);
        else
            printf("%lld\n", query(1, 0, n-1, b-1, c-1));
    }

    return 0;
}