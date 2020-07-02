#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

typedef std::pair<int, int> edge;

int n, m, dfsCount;
std::vector<int> graph[100001];
int dfsNum[100001];
std::stack<edge> edgeStack;
std::vector<std::vector<edge>> bcc;

int DFS(int start, int prev)
{
    int result = dfsNum[start] = ++dfsCount;

    for (int next : graph[start])
    {
        if (next == prev)
            continue;
        
        if (dfsNum[start] > dfsNum[next])
            edgeStack.push({start, next});
        
        if (dfsNum[next] > 0)
            result = std::min(result, dfsNum[next]);
        else
        {
            int nextResult = DFS(next, start);
            result = std::min(result, nextResult);

            if (nextResult >= dfsNum[start])
            {
                bcc.emplace_back();
                std::vector<edge>& currBCC = bcc.back();
                
                while (!edgeStack.empty() && edgeStack.top() != edge(start, next))
                {
                    currBCC.push_back(edgeStack.top());
                    edgeStack.pop();
                }

                currBCC.push_back(edgeStack.top());
                edgeStack.pop();
            }
        }
    }

    return result;
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i)
        if (dfsNum[i] == 0)
            DFS(i, 0);
    
    

    return 0;
}