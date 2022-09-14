#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int INF = INT32_MAX/2;

struct Edge {
    int src, dst, flow, capacity;
    Edge* opposite;

    Edge(int src, int dst, int capacity)
        : src(src), dst(dst), flow(0), capacity(capacity) {}

    void addFlow(int add) {
        flow += add;
        if (opposite) {
            opposite->flow -= add;
        }
    }

    int getSpare() {
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

    void addEdge(int src, int dst, int capacity) {
        Edge* curr = new Edge(src, dst, capacity);
        Edge* oppo = new Edge(dst, src, 0);
        curr->opposite = oppo;
        oppo->opposite = curr;
        graph[src].push_back(curr);
        graph[dst].push_back(oppo);
    }

    int getMaxFlow(int src, int dst) {
        int result = 0;
        std::vector<Edge*> path;

        while (findAugPath(src, dst, path)) {
            int add = INT32_MAX;

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
};

int main() {
    int n, k, d;
    scanf("%d %d %d", &n, &k, &d);

    const int vertexCount = n+d+2;
    const int src = n+d;
    const int dst = n+d+1;
    Graph graph(vertexCount);

    for (int i = 0; i < d; ++i) {
        int limit;
        scanf("%d", &limit);
        graph.addEdge(n+i, dst, limit);
    }

    for (int i = 0; i < n; ++i) {
        graph.addEdge(src, i, k);
        int count;
        scanf("%d", &count);
        for (int j = 0; j < count; ++j) {
            int food;
            scanf("%d", &food);
            graph.addEdge(i, n+food-1, 1);
        }
    }

    printf("%d", graph.getMaxFlow(src, dst));

    return 0;
}