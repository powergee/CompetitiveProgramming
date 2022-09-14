#include <iostream>
#include <algorithm>

int parent[1000001];

int Find(int n)
{
    if (parent[n] < 0) return n;
    return parent[n] = Find(parent[n]);
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);

    if (a != b) parent[b] = a;
}

int main()
{
    std::fill(parent, parent + 1000001, -1);

    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int com, a, b;
        scanf("%d %d %d", &com, &a, &b);

        if (com == 0)
        {
            Union(a, b);
        }
        else if (com == 1)
        {
            if (Find(a) == Find(b))
                printf("YES\n");
            else printf("NO\n");
        }
    }

    return 0;
}