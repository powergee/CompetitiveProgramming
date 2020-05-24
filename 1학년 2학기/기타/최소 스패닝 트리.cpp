#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

std::vector<std::tuple<int, int, int>> edges;

int rank[10001];
int root[10001];

bool Union(int x, int y);
int FindRoot(int num);

bool Union(int x, int y)
{
    x = FindRoot(x);
    y = FindRoot(y);

    if (x == y)
        return false;

    if (rank[x] < rank[y])
        root[x] = y;
    else root[y] = x;

    if (rank[x] == rank[y])
        ++rank[x];

    return true;
}

int FindRoot(int x)
{
    if (root[x] == x)
        return x;
    
    return root[x] = FindRoot(root[x]);
}

int main()
{
    for (int i = 0; i < 10001; ++i)
    {
        root[i] = i;
        rank[i] = 0;
    }

    int v,e;
    scanf("%d %d", &v, &e);

    for (int i = 0; i < e; ++i)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        edges.push_back(std::make_tuple(c, a, b));
    }

    std::sort(edges.begin(), edges.end());

    long long sum = 0;

    for (auto t : edges)
    {
        int a, b, c;
        std::tie(c, a, b) = t;

        if (Union(a, b))
            sum += c;
    }

    printf("%lld", sum);

    return 0;
}