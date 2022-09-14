#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <algorithm>

typedef long long Long;

std::vector<std::tuple<int, int, Long>> edges;
std::vector<Long> dist;
int n, m;
const Long INF = std::numeric_limits<Long>::max();

bool BellmanFord(int vCount)
{
    int start, end;
    Long d;

    for (int i = 0; i < vCount - 1; ++i)
    {
        for (auto& e : edges)
        {
            std::tie(start, end, d) = e;
            if (dist[start] != INF && dist[end] > dist[start] + d)
                dist[end] = dist[start] + d;
        }
    }

    for (auto& e : edges)
    {
        std::tie(start, end, d) = e;
        if (dist[start] != INF && dist[end] > dist[start] + d)
            return false;
    }

    return true;
}

int main()
{
    scanf("%d %d", &n, &m);
    dist.resize(n + 1, INF);
    dist[1] = 0;
    
    for (int i = 0; i < m; ++i)
    {
        int start, end;
        Long dist;
        scanf("%d %d %lld", &start, &end, &dist);
        edges.push_back(std::make_tuple(start, end, dist));
    }

    if (BellmanFord(n))
        for (int i = 2; i <= n; ++i)
            printf("%lld\n", (dist[i] == INF ? -1 : dist[i]));
    else printf("-1");

    return 0;
}