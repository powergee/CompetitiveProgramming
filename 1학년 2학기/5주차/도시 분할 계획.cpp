#include <iostream>
#include <algorithm>
#include <tuple>

void Union(int x, int y);
int Find(int x);

std::tuple<int, int, int> roads[1000001];
int parent[100001];

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

    return parent[x] = Find(parent[x]);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        roads[i] = std::make_tuple(c, a, b);
    }

    std::sort(roads, roads + M);
    for (int i = 0; i < N; ++i)
    {
        parent[i] = i;
    }

    int sum = 0;

    for (int i = 0, addCount = 0; i < M && addCount < N - 2; ++i)
    {
        int a, b, c;
        std::tie(c, a, b) = roads[i];

        if (Find(a) != Find(b))
        {
            sum += c;
            Union(a, b);
            ++addCount;
        }
    }

    printf("%d", sum);

    return 0;
}