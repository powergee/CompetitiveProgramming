#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

typedef long long Long;

struct Variable {
    Long unknown, constant;
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    std::vector<Variable> variable(n+1);
    std::vector<std::tuple<int, int, Long>> edges;
    std::vector<std::vector<std::pair<int, Long>>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        Long sum;
        scanf("%d %d %lld", &u, &v, &sum);
        edges.emplace_back(u, v, sum);
        graph[u].emplace_back(v, sum);
        graph[v].emplace_back(u, sum);
    }

    std::function<void(int, std::vector<bool>&)> calcVariable = [&](int start, std::vector<bool>& visited) {
        visited[start] = true;
        for (auto [next, sum] : graph[start]) {
            if (!visited[next]) {
                variable[next] = { -variable[start].unknown, sum-variable[start].constant };
                calcVariable(next, visited);
            }
        }
    };

    std::vector<bool> visited(n+1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            variable[i] = { 1, 0 };
            calcVariable(i, visited);
        }
    }

    std::fill(visited.begin(), visited.end(), false);
    for (auto [u, v, sum] : edges) {
        auto& v1 = variable[u];
        auto& v2 = variable[v];
        if (v1.unknown + v2.unknown != 0) {
            Long resolved = (sum-v1.constant-v2.constant) / (v1.unknown+v2.unknown);
            v1 = { 0, v1.unknown*resolved + v1.constant };
            calcVariable(u, visited);
        }
    }

    if (std::find_if(variable.begin()+1, variable.end(), [](Variable v) { return v.unknown != 0; }) == variable.end()) {
        for (int i = 1; i <= n; ++i) {
            printf("%lld ", variable[i].constant);
        }
    } else {
        printf("ERROR");
    }

    return 0;
}