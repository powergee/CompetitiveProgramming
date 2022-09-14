#include <iostream>
#include <vector>

std::vector<int> graph[101];
bool visited[101];

int DFS(int start) {
    if (visited[start]) {
        return 0;
    }
    visited[start] = true;

    int result = 1;
    for (int next : graph[start]) {
        result += DFS(next);
    }
    return result;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int s, e;
        scanf("%d %d", &s, &e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    printf("%d", DFS(1)-1);
}