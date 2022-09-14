#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#define INF 100000000
using namespace std;

vector<pair<int, int>> buses[1001];
priority_queue<pair<int, int>> q;
int N, M;
int dist[1001];
bool visited[1001];
int path[1001];

void Dijkstra(int start)
{
    fill(&dist[1], &dist[N] + 1, INF);
    fill(&visited[1], &visited[N] + 1, false);
    fill(&path[1], &path[N] + 1, 0);
    dist[start] = 0;
    
    q.push(make_pair(0, start));
    while (!q.empty())
    {
        int now = q.top().second;
        q.pop();
        if (visited[now])
            continue;

        visited[now] = true;

        for (pair<int, int> bus : buses[now])
        {
            int destination = bus.first;
            int cost = bus.second;
            if (dist[now] + cost < dist[destination])
            {
                dist[destination] = dist[now] + cost;
                path[destination] = now;
                q.push(make_pair(-dist[destination], destination));
            }
        }
    }
}

void PrintPath(int start, int end)
{
    stack<int> s;

    int now = end;
    s.push(now);
    while (now != start)
    {
        now = path[now];
        s.push(now);
    }

    printf("%d\n", s.size());

    while (!s.empty())
    {
        printf("%d ", s.top());
        s.pop();
    }
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int start, end, cost;
        scanf("%d %d %d", &start, &end, &cost);
        buses[start].push_back(make_pair(end, cost));
    }

    int testStart, testEnd;
    scanf("%d %d", &testStart, &testEnd);

    Dijkstra(testStart);
    printf("%d\n", dist[testEnd]);
    PrintPath(testStart, testEnd);

    return 0;
}