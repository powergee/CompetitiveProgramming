#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> canDo[1001];
bool visited[1001];
int matching[1001];

int DFS(int start)
{
    if (visited[start])
        return 0;

    visited[start] = true;

    for (int opposite : canDo[start])
    {
        if (matching[opposite] == 0 || DFS(matching[opposite]))
        {
            matching[opposite] = start;
            return 1;
        }
    }

    return 0;
}

int Bipartite(int N, int K)
{
    int result = 0;

    for (int i = 1; i <= N; ++i)
    {
        int add = 0;
        std::fill(visited, visited + 1001, false);
        add += DFS(i);

        result += add;
    }

    int matched = 0;
    for (int i = 1; i <= N; ++i)
    {
        int add = 0;
        std::fill(visited, visited + 1001, false);
        add += DFS(i);

        result += add;
        matched += add;

        if (matched >= K)
            break;
    }

    return result;
}

int main()
{
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    for (int i = 1; i <= N; ++i)
    {
        int count;
        scanf("%d", &count);

        for (int j = 0; j < count; ++j)
        {
            int work;
            scanf("%d", &work);
            canDo[i].push_back(work);
        }
    }

    printf("%d", Bipartite(N, K));

    return 0;
}