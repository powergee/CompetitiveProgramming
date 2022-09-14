#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#define VERTEX_COUNT 403

struct Edge
{
    int To, Flow, Cap;
    Edge* Oppo;

    Edge(int to, int cap) : To(to), Flow(0), Cap(cap), Oppo(nullptr) {}

    int GetSpare()
    {
        return Cap - Flow;
    }

    void AddFlow(int flow)
    {
        Flow += flow;
        Oppo->Flow -= flow;
    }
};
    
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
    int n, m;
    scanf("%d %d", &n, &m);
    int source = 0, sink = n + m + 1;

    for (int i = 1; i <= n; ++i)
    {
        AddEdge(source, i);

        int count;
        scanf("%d", &count);
        while (count--)
        {
            int target;
            scanf("%d", &target);
            AddEdge(i, target + n);
        }
    }

    for (int i = 1; i <= m; ++i)
        AddEdge(i + n, sink);

    int result = 0;
    bool hasAugPath = true;
    while (hasAugPath)
    {
        std::queue<int> q;
        q.push(source);
        int prev[VERTEX_COUNT];
        Edge* path[VERTEX_COUNT];
        std::fill(prev, prev + VERTEX_COUNT, -1);

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

                    if (sink == next)
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