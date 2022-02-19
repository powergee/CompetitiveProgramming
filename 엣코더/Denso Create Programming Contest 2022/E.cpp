#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<int> vals(n+1);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &vals[i]);
    }

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<std::vector<std::pair<int, int>>> queries(n+1);
    for (int i = 0; i < q; ++i) {
        int v, k;
        scanf("%d %d", &v, &k);
        queries[v].emplace_back(k, i);
    }

    std::vector<int> answer(q);
    std::vector<bool> visited(n+1, false);

    std::function<std::vector<int>(int)> DFS = [&](int start) -> std::vector<int> {
        visited[start] = true;
        std::vector<int> biggest;
        for (int next : graph[start]) {
            if (!visited[next]) {
                auto sub = DFS(next);
                for (int b : sub) {
                    biggest.push_back(b);
                }
            }
        }
        biggest.push_back(vals[start]);
        std::sort(biggest.begin(), biggest.end(), std::greater<int>());
        while (biggest.size() > 20) {
            biggest.pop_back();
        }
        for (auto [k, i] : queries[start]) {
            answer[i] = biggest[k-1];
        }
        return biggest;
    };
    DFS(1);

    for (int ans : answer) {
        printf("%d\n", ans);
    }

    return 0;
}