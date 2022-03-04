#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

typedef long long Long;

struct Edge {
    int u, v;
};

int main() {
    Long n;
    std::cin >> n;
    std::string colors;
    std::cin >> colors;
    colors = " " + colors;

    std::vector<Edge> edges(n-1);
    std::vector<std::vector<Edge*>> tree(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        std::cin >> u >> v;
        edges[i] = { u, v };
        tree[u].push_back(&edges[i]);
        tree[v].push_back(&edges[i]);
    }

    Long answer = n*(n-1) / 2 - (n-1);

    std::vector<Long> neighBlack(n+1, 0), neighWhite(n+1, 0);
    for (int u = 1; u <= n; ++u) {
        for (auto e : tree[u]) {
            int v = (e->u == u ? e->v : e->u);
            (colors[v] == 'B' ? neighBlack : neighWhite)[u]++;
        }
    }
    
    // 3 nodes
    for (int u = 1; u <= n; ++u) {
        if (tree[u].size() <= 1) {
            continue;
        }
        Long same = (colors[u] == 'B' ? neighBlack[u] : neighWhite[u]);
        Long neigh = tree[u].size();
        answer -= (neigh*(neigh-1)/2) - (same*(same-1)/2);
    }

    // 4 nodes
    for (Edge& e : edges) {
        std::pair<Long, Long> left = { neighBlack[e.u], neighWhite[e.u] };
        std::pair<Long, Long> right = { neighBlack[e.v], neighWhite[e.v] };
        (colors[e.u] == 'B' ? right.first : right.second)--;
        (colors[e.v] == 'B' ? left.first : left.second)--;

        if (colors[e.u] == 'B' && colors[e.v] == 'B') {
            answer -= left.second * right.second;
        } else if (colors[e.u] == 'W' && colors[e.v] == 'W') {
            answer -= left.first * right.first;
        } else {
            answer -= left.first * right.second;
            answer -= left.second * right.first;
        }
    }

    printf("%lld\n", answer);

    return 0;
}