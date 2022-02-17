#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <set>

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
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::cout << "Case #" << t << ": ";
        int n;
        std::cin >> n;

        std::vector<std::string> map(n);
        auto getIndex = [n](int r, int c) { return r*n+c; };
        auto isValid = [n](int r, int c) { return 0 <= r && r < n && 0 <= c && c < n; };

        int redCount = 0, blueCount = 0;
        for (int i = 0; i < n; ++i) {
            std::cin >> map[i];
            for (int j = 0; j < n; ++j) {
                if (map[i][j] == 'R') {
                    redCount++;
                } else if (map[i][j] == 'B') {
                    blueCount++;
                }
            }
        }

        if (std::abs(redCount-blueCount) > 1) {
            std::cout << "Impossible\n";
            continue;
        }

        Graph redGraph(n*n+2), blueGraph(n*n+2);
        std::set<std::pair<int, int>> redEdges, blueEdges;
        const int dr[] { 0, 0, 1, -1, 1, -1 };
        const int dc[] { 1, -1, 0, 0, -1, 1 };
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (map[i][j] == '.') {
                    continue;
                }
                for (int k = 0; k < 6; ++k) {
                    int nr = i+dr[k];
                    int nc = j+dc[k];
                    if (isValid(nr, nc) && map[nr][nc] == map[i][j]) {
                        auto& edges = (map[nr][nc] == 'R' ? redEdges : blueEdges);
                        int u = getIndex(i, j);
                        int v = getIndex(nr, nc);
                        if (u > v) {
                            std::swap(u, v);
                        }
                        edges.emplace(u, v);
                    }
                }
            }
        }

        for (auto e : redEdges) {
            redGraph.addEdge(e.first, e.second, 1);
            redGraph.addEdge(e.second, e.first, 1);
        }
        for (auto e : blueEdges) {
            blueGraph.addEdge(e.first, e.second, 1);
            blueGraph.addEdge(e.second, e.first, 1);
        }

        for (int i = 0; i < n; ++i) {
            if (map[0][i] == 'R') {
                redGraph.addEdge(n*n, getIndex(0, i), 1);
            }
            if (map[n-1][i] == 'R') {
                redGraph.addEdge(getIndex(n-1, i), n*n+1, 1);
            }
            if (map[i][0] == 'B') {
                blueGraph.addEdge(n*n, getIndex(i, 0), 1);
            }
            if (map[i][n-1] == 'B') {
                blueGraph.addEdge(getIndex(i, n-1), n*n+1, 1);
            }
        }

        int redPath = redGraph.getMaxFlow(n*n, n*n+1);
        int bluePath = blueGraph.getMaxFlow(n*n, n*n+1);
    
        if (redPath + bluePath >= 2) {
            std::cout << "Impossible\n";
        } else if (redPath) {
            if (redCount < blueCount) {
                std::cout << "Impossible\n";
            } else {
                std::cout << "Red wins\n";
            }
        } else if (bluePath) {
            if (blueCount < redCount) {
                std::cout << "Impossible\n";
            } else {
                std::cout << "Blue wins\n";
            }
        } else {
            std::cout << "Nobody wins\n";
        }
    }
    
    return 0;
}