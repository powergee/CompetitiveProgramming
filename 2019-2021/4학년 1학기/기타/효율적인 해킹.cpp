#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[v].push_back(u);
    }

    auto countComputers = [&](int start) -> int {
        std::vector<bool> visited(n+1, false);
        std::queue<int> q;
        q.push(start);
        visited[start] = true;
        int count = 1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            for (int next : graph[curr]) {
                if (!visited[next]) {
                    visited[next] = true;
                    ++count;
                    q.push(next);
                }
            }
        }
        return count;
    };

    int maxCount = -1;
    std::vector<int> answers;
    for (int i = 1; i <= n; ++i) {
        int currCount = countComputers(i);
        if (currCount > maxCount) {
            maxCount = currCount;
            answers = { i };
        } else if (currCount == maxCount) {
            answers.push_back(i);
        }
    }

    for (int v : answers) {
        printf("%d ", v);
    }

    return 0;
}