#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> edges[101];
int N;
bool visited[101];

void BFS_Modified(int start)
{
    queue<int> q;
    q.push(start);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();

        for (int next : edges[now])
        {
            if (!visited[next])
            {
                visited[next] = true;
                q.push(next);
            }
        }
    }
}

int main()
{
    scanf("%d", &N);

    int input;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            scanf("%d", &input);
            if (input > 0)
                edges[i].push_back(j);
        }
    }

    for (int i = 1; i <= N; ++i)
    {
        fill(visited, visited + 101, false);
        BFS_Modified(i);
        for (int j = 1; j <= N; ++j)
            printf("%d ", visited[j] ? 1 : 0);

        printf("\n");
    }

    return 0;
}