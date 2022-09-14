#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> graph[32001];
int vertexNum[32001];
bool visited[32001];
int post[32001];
int count = 0;

bool Compare(const int& v1, const int& v2)
{
    return post[v1] > post[v2];
}

void DFS(int start)
{
    visited[start] = true;

    for (int next : graph[start])
        if (!visited[next])
            DFS(next);
        
    post[start] = ++count;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
    }

    for (int i = 1; i <= n; ++i)
    {
        vertexNum[i - 1] = i;
        if (!visited[i])
            DFS(i);
    }

    std::sort(vertexNum, vertexNum + n, Compare);

    for (int i = 0; i < n; ++i)
        printf("%d ", vertexNum[i]);

    return 0;
}