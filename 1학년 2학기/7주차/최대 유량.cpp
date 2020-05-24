#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>

typedef long long Long;

Long Res(int start, int end);
Long EdmondsKarp(int source, int sink);
char ScanAlpha();
int AlphaToIndex(char ch);

Long capacity[52][52];
Long flow[52][52];
Long parent[52];

int main()
{
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        char v1, v2;
        Long cap;
        int v1Index, v2Index;

        v1 = ScanAlpha();
        v2 = ScanAlpha();
        scanf("%lld", &cap);

        v1Index = AlphaToIndex(v1);
        v2Index = AlphaToIndex(v2);

        capacity[v1Index][v2Index] += cap;
        capacity[v2Index][v1Index] += cap;
    }

    printf("%lld", EdmondsKarp(AlphaToIndex('A'), AlphaToIndex('Z')));

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
        std::fill(parent, parent + 52, -1);

        std::queue<int> q;
        q.push(source);
        parent[source] = source;

        while (!q.empty() && parent[sink] == -1)
        {
            int now = q.front();
            q.pop();

            for (int next = 0; next < 52; ++next)
            {
                if (Res(now, next) > 0 && parent[next] == -1)
                {
                    parent[next] = now;
                    q.push(next);
                }
            }
        }

        if (parent[sink] == -1)
            break;

        Long ableToFlow = INT64_MAX;

        for (int v = sink; v != source; v = parent[v])
        {
            ableToFlow = std::min(Res(parent[v], v), ableToFlow);
        }

        for (int v = sink; v != source; v = parent[v])
        {
            flow[parent[v]][v] += ableToFlow;
            flow[v][parent[v]] -= ableToFlow;
        }

        result += ableToFlow;
    }

    return result;
}

char ScanAlpha()
{
    char ch = '\0';
    do
    {
        scanf("%c", &ch);
    } while (!(('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')));

    return ch;
}

int AlphaToIndex(char ch)
{
    return ('A' <= ch && ch <= 'Z') ? (ch - 'A') : (ch - 'a' + 26);
}