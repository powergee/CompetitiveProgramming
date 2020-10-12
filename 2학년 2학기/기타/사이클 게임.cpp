#include <iostream>

int parent[500001];

int find(int x)
{
    if (parent[x] == x)
        return x;
    
    return parent[x] = find(parent[x]);
}

void merge(int u, int v)
{
    int uPar = find(u);
    int vPar = find(v);
    if (uPar != vPar)
        parent[uPar] = vPar;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; ++i)
        parent[i] = i;

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        if (find(u) == find(v))
        {
            printf("%d", i+1);
            return 0;
        }
        merge(u, v);
    }

    printf("0");
    return 0;
}