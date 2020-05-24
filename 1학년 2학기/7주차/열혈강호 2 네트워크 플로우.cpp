#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#define START 2001
#define END 2002
#define WorkInd(x) (x+1000)
#define EmplInd(x) (x)

int capacity[2003][2003];
int flow[2003][2003];
int parent[2003];

int Res(int start, int end)
{
    return capacity[start][end] - flow[start][end];
}

int EdmondsKarp(int source, int sink)
{
    int result = 0;

    while (true)
    {
        std::fill(parent, parent + 2003, -1);

        std::queue<int> q;
        q.push(source);
        parent[source] = source;

        while (!q.empty() && parent[sink] == -1)
        {
            int now = q.front();
            q.pop();

            for (int next = 1; next < 2003; ++next)
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

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i)
    {
        int count;
        scanf("%d", &count);

        for (int j = 0; j < count; ++j)
        {
            int work;
            scanf("%d", &work);
            capacity[EmplInd(i)][WorkInd(work)] = 1;
            capacity[WorkInd(work)][END] = 1;
        }
        capacity[START][EmplInd(i)] = 2;
    }

    printf("%d", EdmondsKarp(START, END));

    return 0;
}