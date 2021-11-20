#include <cstdio>
#include <queue>
#include <iostream>
#include <vector>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 1; i <= n; ++i) {
        int j;
        scanf("%d", &j);

        graph[i].push_back(j);
    }

    std::vector<bool> visited(n+1, false);
    std::queue<int> q;
    q.push(x);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (visited[curr]) {
            continue;
        }
        visited[curr] = true;

        for (int next : graph[curr]) {
            if (!visited[next]) {
                q.push(next);
            }

        }
    }

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        if (visited[i]) {
            ++count;
        }
    }
    printf("%d", count);

    return 0;
}
