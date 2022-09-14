#include <iostream>
#include <algorithm>
#include <tuple>

void Union(int x, int y);
int Find(int x);

int parent[300001];
std::pair<int, int> xPos[100001];
std::pair<int, int> yPos[100001];
std::pair<int, int> zPos[100001];
std::tuple<int, int, int> dist[300001];

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
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);

        xPos[i] = {x, i};
        yPos[i] = {y, i};
        zPos[i] = {z, i};
    }

    for (int i = 0; i < N*3; ++i)
    {
        parent[i] = i;
    }

    std::sort(xPos, xPos + N);
    std::sort(yPos, yPos + N);
    std::sort(zPos, zPos + N);
    
    for (int i = 0; i < N - 1; ++i)
    {
        dist[i] = std::make_tuple(xPos[i + 1].first - xPos[i].first, xPos[i].second, xPos[i + 1].second);
        dist[i + (N-1)] = std::make_tuple(yPos[i + 1].first - yPos[i].first, yPos[i].second, yPos[i + 1].second);
        dist[i + (N-1) * 2] = std::make_tuple(zPos[i + 1].first - zPos[i].first, zPos[i].second, zPos[i + 1].second);
    }

    std::sort(dist, dist + (N-1) * 3);

    long long sum = 0;

    for (int i = 0, addCount = 0; i < ((N-1) * 3) && addCount < N - 1; ++i)
    {
        int a, b, c;
        std::tie(c, a, b) = dist[i];

        if (Find(a) != Find(b))
        {
            sum += c;
            Union(a, b);
            ++addCount;
        }
    }

    printf("%lld", sum);

    return 0;
}