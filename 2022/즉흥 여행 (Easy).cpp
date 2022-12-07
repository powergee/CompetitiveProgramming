#include <iostream>
#include <vector>
#include <functional>

bool isConnected(const std::vector<std::vector<int>>& graph, int start) {
    std::vector<bool> visited(graph.size(), false);
    std::function<void(int)> traverse = [&](int curr) {
        visited[curr] = true;
        for (int next : graph[curr]) {
            if (!visited[next]) {
                traverse(next);
            }
        }
    };
    traverse(start);
    return std::all_of(visited.begin()+1, visited.end(), [](bool v) { return v; });
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> plain(n+1), reverse(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        plain[u].push_back(v);
        reverse[v].push_back(u);
    }
    
    std::cout << (isConnected(plain, 1) && isConnected(reverse, 1) ? "Yes" : "No");

    return 0;
}