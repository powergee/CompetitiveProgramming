#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

std::vector<std::tuple<int, int, int>> graph;
int dist[501];
bool visited[501];

bool HasNegCycle(int N)
{
    std::fill(visited, visited + N + 1, false);
    for (int v = 1; v <= N; ++v)
    {
        if (visited[v])
            continue;

        visited[v] = true;
        std::fill(dist, dist + N + 1, 0x7fffffff / 2);
        dist[v] = 0;

        for (int i = 0; i < N - 1; ++i)
        {
            for (auto edge : graph)
            {
                int start, end, time;
                std::tie(start, end, time) = edge;
                if (dist[end] > dist[start] + time)
                {
                    dist[end] = dist[start] + time;
                    visited[end] = true;
                }
            }
        }

        for (auto edge : graph)
        {
            int start, end, time;
            std::tie(start, end, time) = edge;
            if (dist[end] > dist[start] + time)
                return true;
        }
    }

    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        graph.clear();
        int N, M, W;
        scanf("%d %d %d", &N, &M, &W);

        for (int i = 0; i < M; ++i)
        {
            int start, end, time;
            scanf("%d %d %d", &start, &end, &time);
            graph.push_back(std::make_tuple(start, end, time));
            graph.push_back(std::make_tuple(end, start, time));
        }

        for (int i = 0; i < W; ++i)
        {
            int start, end, time;
            scanf("%d %d %d", &start, &end, &time);
            graph.push_back(std::make_tuple(start, end, -time));
        }

        if (HasNegCycle(N))
            printf("YES\n");
        else printf("NO\n");
    }
}