#include <iostream>
#include <vector>

std::vector<int> graph[501];
bool visited[501];

void DFS(int start, int depth) {
    if (depth > 2) {
        return;
    }
    visited[start] = true;

    for (int next : graph[start]) {
        DFS(next, depth+1);
    }
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

    DFS(1, 0);
    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (visited[i]) {
            ++count;
        }
    }

    printf("%d", count-1);
}