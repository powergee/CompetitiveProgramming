#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#define VERTEX_COUNT 402

int flow[VERTEX_COUNT][VERTEX_COUNT];
int capacity[VERTEX_COUNT][VERTEX_COUNT];
int level[VERTEX_COUNT];
int worked[VERTEX_COUNT];

std::vector<int> graph[VERTEX_COUNT];

void AddEdge(int start, int end, int cap)
{
    graph[start].push_back(end);
    graph[end].push_back(start);
    capacity[start][end] += cap;
}

bool BuildLevelGraph(int source, int sink)
{
    std::fill(level, level + VERTEX_COUNT, -1);
    level[source] = 0;
    
    std::queue<int> q;
    q.push(source);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        for (int next : graph[now])
        {
            if (level[next] == -1 && capacity[now][next] - flow[now][next] > 0)
            {
                level[next] = level[now] + 1;
                q.push(next);
            }
        }
    }

    return level[sink] != -1;
}

int AddFlow(int start, int sink, int amount)
{
    if (start == sink)
        return amount;
    
    for (int& i = worked[start]; i < (int)graph[start].size(); ++i)
    {
        int next = graph[start][i];

        if (level[next] == level[start] + 1 && capacity[start][next] - flow[start][next] > 0)
        {
            int ableToFlow = AddFlow(next, sink, std::min(amount, capacity[start][next] - flow[start][next]));
            if (ableToFlow > 0)
            {
                flow[start][next] += ableToFlow;
                flow[next][start] -= ableToFlow;
                return ableToFlow;
            }
        }
    }

    return 0;
}

int Dinic(int source, int sink)
{
    int total = 0;
    while (BuildLevelGraph(source, sink))
    {
        std::fill(worked, worked + VERTEX_COUNT, 0);
        while (true)
        {
            int ableToFlow = AddFlow(source, sink, 1e9);
            if (ableToFlow <= 0)
                break;
            total += ableToFlow;
        }
    }

    return total;
}

int main()
{
    int n, f, d;
    scanf("%d %d %d", &n, &f, &d);

    for (int i = 1; i <= f; ++i)
        AddEdge(0, i, 1);
    for (int i = 1; i <= d; ++i)
        AddEdge(i + 300, 401, 1);
    for (int i = 1; i <= n; ++i)
        AddEdge(i + 100, i + 200, 1);

    for (int i = 1; i <= n; ++i)
    {
        int foodCount, drinkCount;
        scanf("%d %d", &foodCount, &drinkCount);

        for (int j = 0; j < foodCount; ++j)
        {
            int food;
            scanf("%d", &food);
            AddEdge(food, i + 100, 1);
        }

        for (int j = 0; j < drinkCount; ++j)
        {
            int drink;
            scanf("%d", &drink);
            AddEdge(i + 200, drink + 300, 1);
        }
    }

    printf("%d", Dinic(0, 401));

    return 0;
}