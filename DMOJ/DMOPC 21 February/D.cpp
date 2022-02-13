#include <iostream>
#include <vector>
#include <queue>
#include <set>

struct Edge {
    int u, v;

    int getOpposite(int curr) {
        return u == curr ? v : u;
    }

    bool contains(int curr) {
        return curr == u || curr == v;
    }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<Edge> edges(m);
    std::vector<std::vector<Edge*>> graph(n+1);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].u >> edges[i].v;
        graph[edges[i].u].push_back(&edges[i]);
        graph[edges[i].v].push_back(&edges[i]);
    }

    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    auto getMinDist = [&](int start, int end, std::set<int> banned) -> int {
        std::vector<bool> visited(n+1, false);
        std::queue<std::pair<int, int>> q;
        q.emplace(start, 0);
        visited[start] = true;

        while (!q.empty()) {
            auto [curr, dist] = q.front();
            q.pop();
            if (curr == end) {
                return dist;
            }
            
            for (Edge* e : graph[curr]) {
                int next = e->getOpposite(curr);
                if (!visited[next] && banned.count(next) == 0) {
                    q.emplace(next, dist+1);
                    visited[next] = true;
                }
            }
        }
        return INT32_MAX;
    };

    if (getMinDist(c, d, {}) == 1) {
        std::cout << "-1\n";
        return 0;
    }

    int abGlobal = getMinDist(a, b, {});
    int abWithoutC = getMinDist(a, b, {c});
    int abWithoutD = getMinDist(a, b, {d});

    if (abGlobal == abWithoutC) {
        std::cout << "2\n";
        for (int i = 0; i < m; ++i) {
            if (edges[i].contains(c)) {
                std::cout << "2\n";
            } else {
                std::cout << "1\n";
            }
        }
        return 0;
    }

    if (abGlobal == abWithoutD) {
        std::cout << "2\n";
        for (int i = 0; i < m; ++i) {
            if (edges[i].contains(d)) {
                std::cout << "2\n";
            } else {
                std::cout << "1\n";
            }
        }
        return 0;
    }

    if (abWithoutC == INT32_MAX && abWithoutD == INT32_MAX) {
        printf("-1\n");
        return 0;
    } else if (abWithoutC == INT32_MAX) {
        std::cout << "2\n";
        for (int i = 0; i < m; ++i) {
            if (edges[i].contains(d)) {
                std::cout << "2\n";
            } else {
                std::cout << "1\n";
            }
        }
        return 0;
    } else {
        std::cout << "2\n";
        for (int i = 0; i < m; ++i) {
            if (edges[i].contains(c)) {
                std::cout << "2\n";
            } else {
                std::cout << "1\n";
            }
        }
        return 0;
    }

    return 0;
}