#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#define VERTEX_COUNT 401

struct Edge
{
    int To, Capacity, Flow;
    Edge* Oppo;

    Edge(int to, int cap) : To(to), Capacity(cap), Flow(0), Oppo(nullptr) {}

    int GetSpare()
    {
        return Capacity - Flow;
    }

    void AddFlow(int add)
    {
        Flow += add;
        Oppo->Flow -= add;
    }
};

int n, p;
std::vector<Edge*> graph[VERTEX_COUNT];

void AddEdge(int from, int to)
{
    Edge* primary = new Edge(to, 1);
    Edge* opposite = new Edge(from, 0);

    primary->Oppo = opposite;
    opposite->Oppo = primary;

    graph[from].push_back(primary);
    graph[to].push_back(opposite);
}

int main()
{
    scanf("%d %d", &n, &p);

    while (p--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        AddEdge(u, v);
    }

    int source = 1, sink = 2, result = 0;
    bool hasAugPath = true;

    while (hasAugPath)
    {
        int prev[VERTEX_COUNT];
        Edge* path[VERTEX_COUNT];
        std::fill(prev, prev + VERTEX_COUNT, -1);

        std::queue<int> q;
        q.push(source);

        while (!q.empty() && prev[sink] == -1)
        {
            int now = q.front();
            q.pop();

            for (Edge* e : graph[now])
            {
                int next = e->To;

                if (e->GetSpare() > 0 && prev[next] == -1)
                {
                    q.push(next);
                    prev[next] = now;
                    path[next] = e;

                    if (next == sink)
                        break;
                }
            }
        }

        if (prev[sink] == -1)
            hasAugPath = false;
        else
        {
            int flow = INT32_MAX;

            for (int i = sink; i != source; i = prev[i])
                flow = std::min(flow, path[i]->GetSpare());
            
            for (int i = sink; i != source; i = prev[i])
                path[i]->AddFlow(flow);

            result += flow;
        }
    }

    printf("%d", result);

    return 0;
}