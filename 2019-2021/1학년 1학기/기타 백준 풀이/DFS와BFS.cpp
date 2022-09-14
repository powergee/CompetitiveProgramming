#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> graph[1001];

void DFS(int num);
void BFS(int num);

int main()
{
    int n, m, v;
    scanf("%d %d %d", &n, &m, &v);

    while (m--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 0; i < 1001; ++i)
        sort(graph[i].begin(), graph[i].end());

    DFS(v);
    printf("\n");
    BFS(v);
}

void DFS(int num)
{
    static bool visited[1001];

    if (!visited[num])
    {
        printf("%d ", num);
        visited[num] = true;

        for (int next : graph[num])
            if (!visited[next])
                DFS(next);
    }
}

void BFS(int num)
{
    static bool visited[1001];
    static queue<int> q;

    if (!visited[num])
    {
        q.push(num);
        visited[num] = true;

        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            printf("%d ", x);

            for (int near : graph[x])
            {
                if (!visited[near])
                {
                    visited[near] = true;
                    q.push(near);
                }
            }
        }
    }
}