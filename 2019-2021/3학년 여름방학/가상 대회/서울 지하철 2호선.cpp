#include <iostream>
#include <vector>
#include <algorithm>

int n;
std::vector<int> graph[3001];
bool isCycle[3001];
int dist[3001];

void findCycle(int start, int parent) {
    static std::vector<int> dfsStack;
    static bool visited[3001], inStack[3001];

    visited[start] = true;
    inStack[start] = true;
    dfsStack.push_back(start);

    for (int next : graph[start]) {
        if (inStack[next] && next != parent) {
            for (auto iter = dfsStack.rbegin(); iter != dfsStack.rend(); ++iter) {
                isCycle[*iter] = true;
                if (*iter == next) {
                    break;
                }
            }
        }
        if (!visited[next]) {
            findCycle(next, start);
        }
    }
    inStack[start] = false;
    dfsStack.pop_back();
}

void setDist(int start, int currDist) {
    static bool visited[3001];

    visited[start] = true;
    dist[start] = currDist;
    
    for (int next : graph[start]) {
        if (!visited[next]) {
            setDist(next, (isCycle[next] ? 0 : currDist+1));
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    findCycle(1, 0);
    for (int i = 1; i <= n; ++i) {
        if (isCycle[i]) {
            setDist(i, 0);
            break;
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", dist[i]);
    }

    return 0;
}