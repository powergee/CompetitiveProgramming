#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#define VERTEX_COUNT 301

struct Edge
{
    int From, To, Capacity, Flow;
    Edge* Oppo;

    Edge(int from, int to, int cap) : From(from), To(to), Capacity(cap), Flow(0), Oppo(nullptr) {}

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

std::vector<Edge*> graph[VERTEX_COUNT];
std::vector<Edge*> edges;
int prev[VERTEX_COUNT];
Edge *path[VERTEX_COUNT];

void AddEdge(int from, int to, int primaryCap, int oppoCap)
{
    Edge* primary = new Edge(from, to, primaryCap);
    Edge* opposite = new Edge(to, from, oppoCap);

    primary->Oppo = opposite;
    opposite->Oppo = primary;

    graph[from].push_back(primary);
    graph[to].push_back(opposite);
    edges.push_back(primary);
}

bool FindAugPath(int source, int sink)
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
        return false;
    else return true;
}

void EdmondsKarp(int source, int sink)
{
    while (FindAugPath(source, sink))
    {
        int flow = INT32_MAX;

        for (int i = sink; i != source; i = prev[i])
            flow = std::min(flow, path[i]->GetSpare());

        for (int i = sink; i != source; i = prev[i])
            path[i]->AddFlow(flow);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        while (m--)
        {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            AddEdge(u, v, c, 0);
        }

        int source = 1, sink = n;
        EdmondsKarp(source, sink);

        int result = 0;
        for (Edge* e : edges)
        {
            if (e->GetSpare() == 0)
            {
                if (!FindAugPath(e->From, e->To))
                    ++result;
            }
        }
        printf("%d\n", result);

        for (int i = 1; i <= n; ++i)
            graph[i].clear();
        edges.clear();
    }

    return 0;
}