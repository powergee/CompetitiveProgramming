#include <iostream>
#include <algorithm>
#include <vector>
#define INF 100000000
using namespace std;

class Bus
{
public:
    int Start, End, Cost;

    Bus(int s, int e, int c)
    {
        Start = s;
        End = e;
        Cost = c;
    }

    bool operator < (const Bus& e)
    {
        return Cost < e.Cost;
    }
};

int N, M;
int dist[501];
vector<Bus> buses;

bool BellFord(int x)
{
    for (int i = 0; i <= N; ++i)
        dist[i] = INF;

    dist[x] = 0;

    for (int i = 0; i < N - 1; ++i)
    {
        for (Bus b : buses)
        {
            if (dist[b.Start] != INF && dist[b.Start] + b.Cost < dist[b.End])
                dist[b.End] = dist[b.Start] + b.Cost;
        }
    }

    for (Bus b : buses)
    {
        if (dist[b.Start] != INF && dist[b.Start] + b.Cost < dist[b.End])
            return false;
    }
    return true;
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int s, e, c;
        scanf("%d %d %d", &s, &e, &c);
        buses.push_back(Bus(s, e, c));
    }

    if (BellFord(1))
    {
        for (int i = 2; i <= N; ++i)
        {
            printf("%d\n", dist[i] == INF ? -1 : dist[i]);
        }
    }
    else
    {
        printf("%d\n", -1);
    }
    return 0;
}