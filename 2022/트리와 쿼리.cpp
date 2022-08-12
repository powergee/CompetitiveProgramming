#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <numeric>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> depth(n+1, 0), parent(n+1, 0);
    std::function<void(int)> initDepth = [&](int start) {
        for (int next : graph[start]) {
            if (depth[next] == 0) {
                depth[next] = depth[start]+1;
                parent[next] = start;
                initDepth(next);
            }
        }
    };
    depth[1] = 1;
    initDepth(1);

    int q;
    std::cin >> q;
    std::vector<std::vector<int>> lookingFor(n+1);
    std::vector<int> setSize(n+1, 1), query(n);
    while (q--) {
        int count;
        std::cin >> count;
        for (int i = 0; i < count; ++i) {
            std::cin >> query[i];
        }
        std::sort(query.begin(), query.begin()+count, [&](int a, int b) { return depth[a] > depth[b]; });
        for (int i = 0; i < count; ++i) {
            int u = query[i];
            for (int v : lookingFor[u]) {
                setSize[u] += setSize[v];
            }
            lookingFor[parent[u]].push_back(u);
        }

        Long answer = 0;
        for (int i = 0; i < count; ++i) {
            int u = query[i];
            if (setSize[parent[u]] == 1) {
                answer += Long(setSize[u]) * (setSize[u]-1) / 2LL;
            }
        }
        std::cout << answer << "\n";

        for (int i = 0; i < count; ++i) {
            int u = query[i];
            setSize[u] = 1;
            lookingFor[u].resize(0);
            lookingFor[parent[u]].resize(0);
        }
    }

    return 0;
}