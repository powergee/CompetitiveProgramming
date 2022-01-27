#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<std::vector<int>> graph(n+1);
    std::vector<int> group(n+1, 0);
    std::vector<int> seq(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &seq[i]);
    }

    std::function<void(int, int)> DFS = [&](int start, int groupIdx) -> void {
        if (group[start]) {
            return;
        }
        group[start] = groupIdx;
        for (int next : graph[start]) {
            DFS(next, groupIdx);
        }
    };

    int groupIdx = 1;
    for (int i = 1; i <= n; ++i) {
        if (group[i] == 0) {
            DFS(i, groupIdx++);
        }
    }

    int current = group[seq[0]];
    int answer = 0;
    for (int i = 1; i < n; ++i) {
        if (current != group[seq[i]]) {
            ++answer;
        }
        current = group[seq[i]];
    }

    printf("%d", answer);

    return 0;
}