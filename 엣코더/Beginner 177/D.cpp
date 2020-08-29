#include <iostream>
#include <vector>

std::vector<int> graph[200000];
bool visited[200000];

int countPeople(int start)
{
    visited[start] = true;

    int result = 1;
    for (int next : graph[start])
        if (!visited[next])
            result += countPeople(next);
    
    return result;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u-1].push_back(v-1);
        graph[v-1].push_back(u-1);
    }

    int answer = 0;

    for (int i = 0; i < n; ++i)
        if (!visited[i])
            answer = std::max(countPeople(i), answer);
        
    printf("%d", answer);

    return 0;
}