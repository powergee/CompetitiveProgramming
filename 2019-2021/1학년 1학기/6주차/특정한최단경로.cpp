#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define INF 100000000
using namespace std;

vector<pair<int, int>> edges[801];
priority_queue<pair<int, int>> q;
int N, M;
int dist[801];
bool visited[801];
int p1, p2;

struct DijkResult
{
    int StartDist;
    int EndDist;
    int P1Dist;
    int P2Dist;
};

void Dijkstra(int start)
{
    fill(&dist[1], &dist[N] + 1, INF);
    fill(&visited[1], &visited[N] + 1, false);
    dist[start] = 0;
    
    q.push(make_pair(0, start));
    while (!q.empty())
    {
        int now = q.top().second;
        q.pop();
        if (visited[now])
            continue;

        visited[now] = true;

        for (pair<int, int> edge : edges[now])
        {
            int destination = edge.first;
            int cost = edge.second;
            if (dist[now] + cost < dist[destination])
            {
                dist[destination] = dist[now] + cost;
                q.push(make_pair(-dist[destination], destination));
            }
        }
    }
}

DijkResult GetResult()
{
    DijkResult result;
    result.StartDist = dist[1];
    result.EndDist = dist[N];
    result.P1Dist = dist[p1];
    result.P2Dist = dist[p2];
    return result;
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int start, end, cost;
        scanf("%d %d %d", &start, &end, &cost);
        edges[start].push_back(make_pair(end, cost));
        edges[end].push_back(make_pair(start, cost));
    }

    scanf("%d %d", &p1, &p2);

    Dijkstra(1);
    DijkResult dijkStart = GetResult();
    Dijkstra(p1);
    DijkResult dijkP1 = GetResult();
    Dijkstra(p2);
    DijkResult dijkP2 = GetResult();

    int minCost = min(dijkStart.P1Dist + dijkP1.P2Dist + dijkP2.EndDist,
                     dijkStart.P2Dist + dijkP2.P1Dist + dijkP1.EndDist);
    printf("%d", minCost >= INF ? -1 : minCost);
    return 0;
}