#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

std::vector<int> graph;
std::vector<std::vector<int>> reverse;
std::vector<bool> visited;

void DFS(int start, std::stack<int>& st)
{
    if (visited[start])
        return;

    visited[start] = true;

    if (graph[start] != -1 && !visited[graph[start]])
        DFS(graph[start], st);

    st.push(start);
}

int visitCount = 0;
void DFSReverse(int start)
{
    if (visited[start])
        return;

    visited[start] = true;
    ++visitCount;

    for (int next : reverse[start])
        DFSReverse(next);
}

int main()
{
    int n;
    scanf("%d", &n);

    graph.resize(n + 1);
    reverse.resize(n + 1);
    visited.resize(n + 1);
    std::fill(graph.begin(), graph.end(), -1);
    std::fill(visited.begin(), visited.end(), false);

    for (int start = 1; start <= n; ++start)
    {
        int end;
        scanf("%d", &end);
        graph[start] = end;
        reverse[end].push_back(start);
    }

    std::stack<int> sccStack;
    for (int i = 1; i <= n; ++i)
        DFS(i, sccStack);
    
    std::fill(visited.begin(), visited.end(), false);

    int result = 0;
    while (!sccStack.empty())
    {
        int now = sccStack.top();
        sccStack.pop();

        if (visited[now])
            continue;

        DFSReverse(now);
        
        if (visitCount == 1)
        {
            if (now == graph[now])
            {
                ++result;
            }
        }
        else result += visitCount;

        visitCount = 0;
    }

    printf("%d", result);
}