#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d", &n);
        int order[n];
        std::set<int> graph[n+1];

        for (int i = 0; i < n; ++i) {
            scanf("%d", order+i);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                graph[order[i]].insert(order[j]);
            }
        }

        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);

            std::set<int>::iterator found;
            if ((found = graph[u].find(v)) != graph[u].end()) {
                graph[u].erase(found);
                graph[v].insert(u);
            } else {
                graph[v].erase(graph[v].find(u));
                graph[u].insert(v);
            }
        }

        std::vector<bool> visited(n+1, false), inStack(n+1, false);

        std::function<bool(int)> findCycle;
        findCycle = [&](int start) -> bool {
            visited[start] = true;
            inStack[start] = true;

            for (int next : graph[start]) {
                if (inStack[next] || (!visited[next] && findCycle(next))) {
                    return true;
                }
            }

            inStack[start] = false;
            return false;
        };

        auto hasCycle = [&]() -> bool {
            for (int u = 1; u <= n; ++u) {
                if (!visited[u] && findCycle(u)) {
                    return true;
                }
            }
            return false;
        };

        if (hasCycle()) {
            printf("IMPOSSIBLE\n");
        } else {
            std::vector<int> inorder(n+1, 0), prevVisited(n+1, 0), answer;
            bool isUnique = true;
            std::queue<int> q;

            for (int u = 1; u <= n; ++u) {
                for (int v : graph[u]) {
                    inorder[v]++;
                }
            }
            for (int u = 1; u <= n; ++u) {
                if (inorder[u] == 0) {
                    q.push(u);
                }
            }

            while (!q.empty()) {
                if (q.size() >= 2) {
                    isUnique = false;
                    break;
                }

                int curr = q.front();
                q.pop();
                answer.push_back(curr);

                for (int next : graph[curr]) {
                    prevVisited[next]++;
                    if (prevVisited[next] == inorder[next]) {
                        q.push(next);
                    }
                }
            }

            if (isUnique) {
                for (int ans : answer) {
                    printf("%d ", ans);
                }
                printf("\n");
            } else {
                printf("?\n");
            }
        }
    }

    return 0;
}