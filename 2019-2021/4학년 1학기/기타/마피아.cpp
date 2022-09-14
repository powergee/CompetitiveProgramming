#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <set>

typedef long long Long;

struct Edge {
    int src, dst;
    Long flow, capacity, id;
    Edge* opposite;

    Edge(int src, int dst, Long capacity, int id)
        : src(src), dst(dst), flow(0), capacity(capacity), id(id) {}

    void addFlow(Long add) {
        flow += add;
        if (opposite) {
            opposite->flow -= add;
        }
    }

    Long getSpare() {
        return capacity-flow;
    }
};

class Graph {
private:
    std::vector<std::vector<Edge*>> graph;

    bool findAugPath(int src, int dst, std::vector<Edge*>& path) {
        std::vector<Edge*> prev(graph.size(), nullptr);
        std::queue<int> q;
        q.push(src);

        while (!q.empty() && prev[dst] == nullptr) {
            int u = q.front();
            q.pop();

            for (Edge* e : graph[u]) {
                int v = e->dst;
                if (e->getSpare() > 0 && v != src && u != v && prev[v] == nullptr) {
                    q.push(v);
                    prev[v] = e;
                    if (prev[dst]) {
                        break;
                    }
                }
            }
        }

        if (prev[dst]) {
            path.resize(0);
            for (Edge* e = prev[dst]; e != nullptr; e = prev[e->src]) {
                path.push_back(e);
            }
            return true;
        }
        return false;
    }

public:
    const static Long INF = INT64_MAX/2;

    Graph(int vertexCount) {
        graph.resize(vertexCount);
    }

    ~Graph() {
        for (auto& edges : graph) {
            for (Edge* e : edges) {
                if (e) { delete e; }
            }
        }
    }

    void addEdge(int src, int dst, Long capacity, int id) {
        Edge* curr = new Edge(src, dst, capacity, id);
        Edge* oppo = new Edge(dst, src, 0, id);
        curr->opposite = oppo;
        oppo->opposite = curr;
        graph[src].push_back(curr);
        graph[dst].push_back(oppo);
    }

    int getMaxFlow(int src, int dst) {
        Long result = 0;
        std::vector<Edge*> path;

        while (findAugPath(src, dst, path)) {
            Long add = INT64_MAX;

            for (Edge* e : path) {
                add = std::min(add, e->getSpare());
            }
            for (Edge* e : path) {
                e->addFlow(add);
            }

            result += add;
        }

        return result;
    }

    int getMaxFlowMinCut(int src, int dst, std::set<int>& cutResult) {
        Long maxFlow = getMaxFlow(src, dst);
        std::vector<bool> visited(graph.size(), false);
        std::queue<int> q;
        q.push(src);
        visited[src] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (Edge* e : graph[u]) {
                int v = e->dst;
                if (e->getSpare() > 0 && !visited[v]) {
                    q.push(v);
                    visited[v] = true;
                }
            }
        }

        for (const auto& edges : graph) {
            for (Edge* e : edges) {
                if (visited[e->src] && !visited[e->dst]) {
                    cutResult.insert(e->id);
                }
            }
        }
        return maxFlow;
    }
};

int main() {
    int n, m, src, dst;
    scanf("%d %d", &n, &m);
    scanf("%d %d", &src, &dst);
    --src, --dst;

    Graph graph(2*n);

    auto getEntrance = [&](int v) { return 2*v; };
    auto getExit = [&](int v) { return 2*v+1; };

    for (int i = 0; i < n; ++i) {
        int cost;
        scanf("%d", &cost);
        graph.addEdge(getEntrance(i), getExit(i), cost, i+1);
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        graph.addEdge(getExit(u), getEntrance(v), Graph::INF, -(i+1));
        graph.addEdge(getExit(v), getEntrance(u), Graph::INF, -(i+1));
    }

    std::set<int> result;
    graph.getMaxFlowMinCut(getEntrance(src), getExit(dst), result);
    for (int v : result) {
        if (v > 0) {
            printf("%d ", v);
        }
    }

    return 0;
}