#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
#include <map>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, T, m;
    std::cin >> n >> T >> m;

    int s, e;
    std::cin >> s >> e;
    
    std::vector<std::vector<int>> dist(2, std::vector<int>(n, INT32_MAX / 2));
    std::vector<int> mentioned(m*2);
    dist[0][s] = dist[1][s] = 0;
    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            std::cin >> u >> v >> w;
            dist[1][v] = std::min(dist[1][v], dist[0][u] + w);
            dist[1][u] = std::min(dist[1][u], dist[0][v] + w);
            mentioned[i*2] = u;
            mentioned[i*2+1] = v;
        }
        for (int i = 0; i < m*2; ++i) {
            dist[0][mentioned[i]] = dist[1][mentioned[i]];
        }
    }

    std::cout << (dist[0][e] == INT32_MAX/2 ? -1 : dist[0][e]);

    return 0;
}