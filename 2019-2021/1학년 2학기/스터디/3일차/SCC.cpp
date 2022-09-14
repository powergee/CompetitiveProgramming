#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

std::vector<int> graph[10001];
std::vector<int> reverse[10001];
std::stack<int> s;
std::vector<std::vector<int>> SCCs;
std::vector<int> found;
bool visited[10001];
bool visited_Reverse[10001];

void DFS(int start)
{
    if (visited[start])
        return;

    visited[start] = true;

    for (auto ele : graph[start])
    {
        if (!visited[ele])
            DFS(ele);
    }
    s.push(start);
}

void DFS_Reverse(int start)
{
    if (visited_Reverse[start])
        return;
    
    visited_Reverse[start] = true;
    
    found.push_back(start);

    for (auto ele : reverse[start])
    {
        if (!visited_Reverse[ele])
            DFS_Reverse(ele);
    }
}

bool CompareVector(std::vector<int>& v1, std::vector<int>& v2)
{
    return (*v1.begin() < *v2.begin());
}

int main()
{
    int V, E;
    scanf("%d %d", &V, &E);

    for (int i = 0; i < E; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        reverse[b].push_back(a);
    }

    for (int i = 1; i <= V; ++i)
    {
        if (!visited[i])
            DFS(i);
    }

    while (!s.empty())
    {
        int now = s.top();
        s.pop();

        if (!visited_Reverse[now])
        {
            found.clear();
            DFS_Reverse(now);
            if (!found.empty())
            {
                std::sort(found.begin(), found.end());
                SCCs.push_back(found);
            }
        }

    }

    printf("%d\n", SCCs.size());
    std::sort(SCCs.begin(), SCCs.end(), CompareVector);
    
    for (std::vector<int> v : SCCs)
    {
        for (int n : v)
            printf("%d ", n);
        printf("-1\n");
    }

    return 0;
}