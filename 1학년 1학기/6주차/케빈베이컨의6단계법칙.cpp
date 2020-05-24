#include <iostream>
#include <algorithm>
#include <vector>
#define INF 10000000
using namespace std;

int N, M;
int edges[101][101];
int dist[101][101];
int path[101][101];

int GetKevinNum(int vertex)
{
    int length;
    int sum = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (i == vertex) continue;

        length = 0;
        int startPoint = vertex;
        while (startPoint != i)
        {
            startPoint = path[startPoint][i];
            ++length;
        }
        
        sum += length;
    }
    return sum;
}

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[a][b] = 1;
        edges[b][a] = 1;
    }

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            if (i == j)
                dist[i][j] = 0;

            else if (edges[i][j])
            {
                dist[i][j] = edges[i][j];
                path[i][j] = j;
            }
            else dist[i][j] = INF;
        }

    for (int k = 1; k <= N; ++k)
    {
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    // <int:케빈베이컨의 수, int:번호>
    vector<pair<int, int>> rank;

    for (int i = 1; i <= N; ++i)
    {
        int kevin = GetKevinNum(i);
        rank.push_back(make_pair(kevin, i));
    }

    sort(rank.begin(), rank.end());

    printf("%d", (*rank.begin()).second);

    return 0;
}