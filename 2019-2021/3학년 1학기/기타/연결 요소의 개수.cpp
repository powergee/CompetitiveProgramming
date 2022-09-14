#include <iostream>
#include <vector>

std::vector<int> graph[1001];
bool visited[1001];

void DFS(int start) {
    if (visited[start]) {
        return;
    }
    visited[start] = true;

    for (int next : graph[start]) {
        DFS(next);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int s, e;
        scanf("%d %d", &s, &e);
        graph[s].push_back(e);
        graph[e].push_back(s);
    }

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            DFS(i);
            ++answer;
        }
    }

    printf("%d", answer);
}