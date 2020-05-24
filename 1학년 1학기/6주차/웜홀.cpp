#include <iostream>
#include <algorithm>
#include <vector>
#define INF 100000000
using namespace std;

class Edge
{
public:
    int Start, End, Time;

    Edge(int s, int e, int c)
    {
        Start = s;
        End = e;
        Time = c;
    }

    bool operator < (const Edge& e)
    {
        return Time < e.Time;
    }
};

int TC;
int S, E, T;
vector<Edge> edges;

int dist[501];

bool BellFord(int start)
{
    fill(dist, dist + 501, INF);
    dist[start] = 0;

    for (int i = 0; i < S - 1; ++i)
    {
        for (Edge e : edges)
        {
            // 도로일 때
            if (e.Time >= 0)
            {
                if (dist[e.Start] + e.Time < dist[e.End])
                    dist[e.End] = dist[e.Start] + e.Time;

                if (dist[e.End] + e.Time < dist[e.Start])
                    dist[e.Start] = dist[e.End] + e.Time;
            }
            // 웜홀일 때
            else
            {
                if (dist[e.Start] + e.Time < dist[e.End])
                    dist[e.End] = dist[e.Start] + e.Time;
            }
        }
    }

    for (Edge e : edges)
    {
        // 도로일 때
        if (e.Time >= 0)
        {
            if (dist[e.Start] + e.Time < dist[e.End] || dist[e.End] + e.Time < dist[e.Start])
                return false;
        }
        // 웜홀일 때
        else
        {
            if (dist[e.Start] + e.Time < dist[e.End])
                return false;
        }
    }

    return true;
}

bool CheckPossibility(int start)
{
    if (!BellFord(start))
        return true;

    for (int i = 1; i <= S; ++i)
    {
        if (dist[i] < 0)
            return true;
    }

    return false;
}

int main()
{
    scanf("%d", &TC);

    for (int i = 0; i < TC; ++i)
    {
        edges.clear();
        scanf("%d %d %d", &S, &E, &T);
        int start, end, time;

        for (int j = 0; j < E; ++j)
        {
            scanf("%d %d %d", &start, &end, &time);
            edges.push_back(Edge(start, end, time));
        }

        for (int j = 0; j < T; ++j)
        {
            scanf("%d %d %d", &start, &end, &time);
            edges.push_back(Edge(start, end, -time));
        }

        bool possible = CheckPossibility(1);

        if (possible)
            printf("YES\n");
        else printf("NO\n");
    }
}