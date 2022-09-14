#include <iostream>
#include <queue>
using namespace std;

const int INF = 0x7fffffff;

vector<pair<int, int>> edges[20001];
int dist[20001];
int V, E, start;
bool visited[20001];

int main()
{
    scanf("%d %d", &V, &E);
    scanf("%d", &start);

    for (int i = 0; i < E; ++i)
    {
        int u, v, m;
        scanf("%d %d %d", &u, &v, &m);
        edges[u].push_back(make_pair(v, m));
    }

    for (int i = 1; i <= 20000; ++i)
        dist[i] = INF;

    dist[start] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, start));

    while (!q.empty())
    {
        int now = q.top().second; q.pop();
        if (visited[now]) continue;
        visited[now] = true;

        for (pair<int, int> edge : edges[now])
        {
            int next = edge.first;
            int cost = edge.second;
            if (dist[now] + cost < dist[next])
            {
                dist[next] = dist[now] + cost;
                q.push(make_pair(-dist[next], next));
            }
        }
    }

    for (int i = 1; i <= V; ++i)
    {
        if (dist[i] == INF)
            printf("INF\n");
        else printf("%d\n", dist[i]);
    }

    return 0;
}