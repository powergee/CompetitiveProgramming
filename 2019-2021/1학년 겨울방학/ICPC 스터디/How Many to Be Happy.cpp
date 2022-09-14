#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define VERTEX_COUNT 101

struct Edge
{
    int From, To, Cost, Flow;
    Edge* Oppo;

    Edge(int from, int to, int cost) : From(from), To(to), Cost(cost), Flow(0), Oppo(nullptr) {}

    int GetSpare()
    {
        return 1 - Flow;
    }

    void AddFlow(int add)
    {
        Flow += add;
        Oppo->Flow -= add;
    }
};

std::vector<Edge*> graph[VERTEX_COUNT];
std::vector<Edge*> edges;
int prev[VERTEX_COUNT];
Edge *path[VERTEX_COUNT];

void AddEdge(int from, int to, int cost)
{
    Edge* primary = new Edge(from, to, cost);
    Edge* opposite = new Edge(to, from, cost);

    primary->Oppo = opposite;
    opposite->Oppo = primary;

    graph[from].push_back(primary);
    graph[to].push_back(opposite);
    edges.push_back(primary);
}

bool FindAugPath(int source, int sink, int maxCost)
{
    std::fill(prev, prev + VERTEX_COUNT, -1);
    std::queue<int> q;
    q.push(source);

    while (!q.empty() && prev[sink] == -1)
    {
        int now = q.front();
        q.pop();

        for (Edge *e : graph[now])
        {
            int next = e->To;

            if (e->GetSpare() > 0 && prev[next] == -1 && e->Cost < maxCost)
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
        return false;
    else return true;
}

int EdmondsKarp(int source, int sink, int maxCost)
{
    for (Edge* e : edges)
    {
        e->Flow = 0;
        e->Oppo->Flow = 0;
    }

    int result = 0;
    while (FindAugPath(source, sink, maxCost))
    {
        int flow = INT32_MAX;

        for (int i = sink; i != source; i = prev[i])
            flow = std::min(flow, path[i]->GetSpare());

        for (int i = sink; i != source; i = prev[i])
            path[i]->AddFlow(flow);

        result += flow;
    }

    return result;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    while (m--)
    {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        AddEdge(u, v, cost);
    }

    int result = 0;
    for (Edge* e : edges)
        result += std::min(EdmondsKarp(e->From, e->To, e->Cost), EdmondsKarp(e->To, e->From, e->Cost));
        
    printf("%d", result);

    return 0;
}