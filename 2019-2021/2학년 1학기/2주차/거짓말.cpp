#include <iostream>
#include <vector>

std::vector<int> graph[51];
std::vector<int> party[50];
bool visited[51];

void DFS(int start)
{
    if (visited[start])
        return;

    visited[start] = true;

    for (int next : graph[start])
        if (!visited[next])
            DFS(next);
}

int main()
{
    int n, m, k;
    std::vector<int> know;
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 0; i < k; ++i)
    {
        int num;
        scanf("%d", &num);
        know.push_back(num);
    }

    for (int i = 0; i < m; ++i)
    {
        int count;
        scanf("%d", &count);

        for (int j = 0; j < count; ++j)
        {
            int num;
            scanf("%d", &num);
            party[i].push_back(num);
        }

        for (int j = 0; j < count - 1; ++j)
        {
            graph[party[i][j]].push_back(party[i][j + 1]);
            graph[party[i][j + 1]].push_back(party[i][j]);
        }
    }

    for (int num : know)
        DFS(num);

    int answer = 0;
    for (int i = 0; i < m; ++i)
    {
        bool able = true;
        for (int j = 0; j < (int)party[i].size() && able; ++j)
            able = !visited[party[i][j]];

        if (able)
            ++answer;
    }

    printf("%d", answer);

    return 0;
}