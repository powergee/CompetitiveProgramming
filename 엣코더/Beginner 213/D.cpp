#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> graph[200001];
bool visited[200001];

void DFS(int start) {
    printf("%d ", start);
    visited[start] = true;

    for (int next : graph[start]) {
        if (!visited[next]) {
            DFS(next);
            printf("%d ", start);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; ++i) {
        std::sort(graph[i].begin(), graph[i].end());
    }

    DFS(1);

    return 0;
}