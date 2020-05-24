#include <iostream>

int parent[1000001];

void Union(int, int);
int Find(int);

void Union(int x, int y)
{
    int xPar = Find(x);
    int yPar = Find(y);

    parent[xPar] = yPar;
}

int Find(int x)
{
    if (x == parent[x])
        return x;

    parent[x] = Find(parent[x]);
    return parent[x];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }

    for (int i = 0; i < m; ++i)
    {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);

        if (op == 0)
        {
            Union(a, b);
        }

        else if (op == 1)
        {
            if (Find(a) == Find(b))
                printf("YES\n");
            else printf("NO\n");
        }
    }

    return 0;
}