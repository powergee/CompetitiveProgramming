#include <vector>
#include <queue>
#include <algorithm>

const int INF = INT32_MAX/2;

struct Edge {
    int src, dst, flow, cost, capacity;
    Edge* opposite;

    Edge(int src, int dst, int cost, int capacity)
        : src(src), dst(dst), flow(0), cost(cost), capacity(capacity) {}

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

struct MCMF {
    int flowed, totalCost;
};

class Graph {
private:
    std::vector<std::vector<Edge*>> graph;

    bool findAugPath(int src, int dst, std::vector<Edge*>& path) {
        std::vector<Edge*> prev(graph.size(), nullptr);
        std::vector<int> dist(graph.size(), INF);
        std::vector<bool> inQueue(graph.size(), false);
        std::queue<int> q;

        dist[src] = 0;
        inQueue[src] = true;
        q.push(src);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = false;

            for (Edge* e : graph[u]) {
                if (e->getSpare() <= 0) {
                    continue;
                }
                int v = e->dst;
                if (dist[u] + e->cost < dist[v]) {
                    dist[v] = dist[u] + e->cost;
                    prev[v] = e;
                    if (!inQueue[v]) {
                        inQueue[v] = true;
                        q.push(v);
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

    void addEdge(int src, int dst, int cost, int capacity) {
        Edge* curr = new Edge(src, dst, cost, capacity);
        Edge* oppo = new Edge(dst, src, -cost, 0);
        curr->opposite = oppo;
        oppo->opposite = curr;
        graph[src].push_back(curr);
        graph[dst].push_back(oppo);
    }

    MCMF getMinCostMaxFlow(int src, int dst) {
        MCMF result = { 0, 0 };
        std::vector<Edge*> path;

        while (findAugPath(src, dst, path)) {
            int add = INT32_MAX;
            int costSum = 0;

            for (Edge* e : path) {
                add = std::min(add, e->getSpare());
            }
            for (Edge* e : path) {
                e->addFlow(add);
                costSum += e->cost;
            }

            result.flowed += add;
            result.totalCost += costSum * add;
        }

        return result;
    }
};