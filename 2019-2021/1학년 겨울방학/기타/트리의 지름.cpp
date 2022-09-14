#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<int> farthest;
std::vector<bool> visited;

int GetMaxDist(int start)
{
    visited[start] = true;

    int result = 0;
    int& farNext = farthest[start];
    for (auto next : graph[start])
    {
        if (!visited[next.first])
        {
            int dist = GetMaxDist(next.first) + next.second;
            if (result < dist)
            {
                result = dist;
                farNext = next.first;
            }
        }
    }

    return result;
}

int main()
{
    int v;
    scanf("%d", &v);
    graph.resize(v + 1);
    farthest.resize(v + 1, -1);
    visited.resize(v + 1, false);

    for (int i = 0; i < v; ++i)
    {
        int p;
        scanf("%d", &p);

        while (true)
        {
            int q, dist;
            scanf("%d", &q);

            if (q == -1)
                break;

            scanf("%d", &dist);
            graph[p].push_back({q, dist});
        }
    }

    GetMaxDist(1);
    int start;
    for (start = farthest[1]; farthest[start] != -1; start = farthest[start]);
    std::fill(visited.begin(), visited.end(), false);
    printf("%d", GetMaxDist(start));
}