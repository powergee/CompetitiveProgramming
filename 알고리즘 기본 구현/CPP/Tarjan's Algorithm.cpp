#include <iostream>
#include <vector>
#include <functional>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, e;
    std::cin >> n >> e;

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < e; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
    }

    using SCC = std::vector<int>;
    std::vector<SCC> sccs;
    std::vector<int> recStack, visited(n+1, 0);
    std::vector<bool> finished(n+1, false);
    int id = 1;

    std::function<int(int)> findParentByDFS = [&](int start) -> int {
        int parent = start;
        visited[start] = id++;
        recStack.push_back(start);

        for (int next : graph[start]) {
            if (!visited[next]) {
                int found = findParentByDFS(next);
                parent = (visited[found] < visited[parent] ? found : parent);
            } else if (!finished[next]) {
                parent = (visited[next] < visited[parent] ? next : parent);
            }
        }

        if (parent == start) {
            sccs.emplace_back();
            int top;
            do {
                top = recStack.back();
                recStack.pop_back();
                finished[top] = true;
                sccs.back().push_back(top);
            } while (top != parent);
            std::sort(sccs.back().begin(), sccs.back().end());
        }

        return parent;
    };
    
    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            findParentByDFS(v);
        }
    }

    std::cout << sccs.size() << "\n";
    std::sort(sccs.begin(), sccs.end(), [](auto& s1, auto& s2) { return s1[0] < s2[0]; });
    for (auto& scc : sccs) {
        for (int v : scc) {
            std::cout << v << " ";
        }
        std::cout << "-1\n";
    }

    return 0;
}