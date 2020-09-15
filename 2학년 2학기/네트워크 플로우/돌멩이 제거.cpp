#include <iostream>
#include <vector>
#include <algorithm>
#define LEFT_MAX 501
#define RIGHT_MAX 501

std::vector<int> connected[LEFT_MAX];
bool visited[LEFT_MAX];
int matching[RIGHT_MAX];

int DFS(int start)
{
    if (visited[start])
        return 0;

    visited[start] = true;

    for (int opposite : connected[start])
    {
        if (matching[opposite] == 0 || DFS(matching[opposite]))
        {
            matching[opposite] = start;
            return 1;
        }
    }

    return 0;
}

int bipartite(int N)
{
    int result = 0;

    for (int i = 1; i <= N; ++i)
    {
        std::fill(visited, visited + N+1, false);
        result += DFS(i);
    }

    return result;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; ++i)
    {
        int r, c;
        scanf("%d %d", &r, &c);
        connected[r].push_back(c);
    }

    printf("%d", bipartite(n));

    return 0;
}