#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

struct Edge
{
    int To, Capacity, Flow;
    Edge* Opposite;

    Edge(int to, int cap) : To(to), Capacity(cap), Flow(0), Opposite(nullptr) {}

    int GetSpare()
    {
        return Capacity - Flow;
    }

    void AddFlow(int add)
    {
        Flow += add;
        Opposite->Flow -= add;
    }
};

int ToIndex(char alpha)
{
    if ('a' <= alpha && alpha <= 'z')
        return alpha - 'a';
    else return alpha - 'A' + 26;
}

std::vector<Edge*> graph[52];

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        char u, v;
        int c;
        scanf(" %c %c %d", &u, &v, &c);

        int uIndex = ToIndex(u);
        int vIndex = ToIndex(v);

        Edge* primary = new Edge(vIndex, c);
        Edge* opposite = new Edge(uIndex, c);

        primary->Opposite = opposite;
        opposite->Opposite = primary;

        graph[uIndex].push_back(primary);
        graph[vIndex].push_back(opposite);
    }

    int result = 0;
    int source = ToIndex('A');
    int sink = ToIndex('Z');
    bool hasAugPath = true;

    while (hasAugPath)
    {
        int prev[52];
        Edge* path[52] = {0, };
        std::fill(prev, prev + 52, -1);
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