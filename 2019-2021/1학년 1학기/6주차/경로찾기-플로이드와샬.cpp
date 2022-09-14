#include <iostream>
#include <algorithm>
#define INF 100000000
using namespace std;

int edges[101][101];
int dist[101][101];
int N;

int main()
{
    scanf("%d", &N);

    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= N; ++j)
            scanf("%d", &edges[i][j]);

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (edges[i][j]) dist[i][j] = edges[i][j];
            else dist[i][j] = INF;
        }

    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            //printf("%d ", dist[i][j]);
            if (dist[i][j] != INF) printf("1 ");
            else printf("0 ");
        }
        
        printf("\n");
    }

    return 0;
}
