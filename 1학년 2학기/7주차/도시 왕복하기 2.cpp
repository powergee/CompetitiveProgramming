#include <iostream>
#include <algorithm>
#include <queue>

typedef long long Long;

Long Res(int start, int end);
Long EdmondsKarp(int source, int sink);

Long capacity[801][801];
Long flow[801][801];
Long parent[801];

int main()
{
    int N, P;
    scanf("%d %d", &N, &P);

    for (int i = 0; i < P; ++i)
    {
        int start, end;
        scanf("%d %d", &start, &end);

        capacity[start + 400][end] += 1;
        capacity[end + 400][start] += 1;
        capacity[start][start + 400] = 1;
        capacity[end][end + 400] = 1;
    }

    printf("%lld", EdmondsKarp(1 + 400, 2));

    return 0;
}

Long Res(int start, int end)
{
    return capacity[start][end] - flow[start][end];
}

Long EdmondsKarp(int source, int sink)
{
    Long result = 0;

    while (true)
    {
        std::fill(parent, parent + 801, -1);

        std::queue<int> q;
        q.push(source);
        parent[source] = source;

        while (!q.empty() && parent[sink] == -1)
        {
            int now = q.front();
            q.pop();

            for (int next = 1; next <= 800; ++next)
            {
                if (Res(now, next) > 0 && parent[next] == -1)
                {
                    q.push(next);
                    parent[next] = now;
                }
            }
        }

        if (parent[sink] == -1)
            break;

        for (int v = sink; v != source; v = parent[v])
        {
            flow[parent[v]][v] += 1;
            flow[v][parent[v]] -= 1;
        }

        result += 1;
    }

    return result;
}