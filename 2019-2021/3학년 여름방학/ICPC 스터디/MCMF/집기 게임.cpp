#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define INF ((__INT32_MAX__)/2)
#define SRC 401
#define DST 402
#define VERTEX_COUNT 403

int cost[VERTEX_COUNT][VERTEX_COUNT];
int flow[VERTEX_COUNT][VERTEX_COUNT];
int capa[VERTEX_COUNT][VERTEX_COUNT];
int prev[VERTEX_COUNT];
int dist[VERTEX_COUNT];
bool inQueue[VERTEX_COUNT];

void addEdge(int src, int dst, int currCost, int currCapa) {
    cost[src][dst] = currCost;
    cost[dst][src] = -currCost;
    capa[src][dst] = currCapa;
}

int getSpare(int u, int v) {
    return capa[u][v] - flow[u][v];
}

void addFlow(int u, int v, int add) {
    flow[u][v] += add;
    flow[v][u] -= add;
}

bool findAugPath(int src, int dst) {
    std::fill(prev, prev + VERTEX_COUNT, -1);
    std::fill(dist, dist + VERTEX_COUNT, INF);
    std::queue<int> q;
    
    dist[src] = 0;
    inQueue[src] = true;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        inQueue[u] = false;
        q.pop();

        for (int v = 1; v <= VERTEX_COUNT; ++v) {
            if (getSpare(u, v) <= 0) {
                continue;
            }
            if (dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                prev[v] = u;
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return prev[dst] != -1;
}

struct MCMFResult {
    int flowed, cost;
};

MCMFResult MCMF(int source, int sink) {
    MCMFResult result = { 0, 0 };

    while (findAugPath(source, sink)) {
        int add = __INT32_MAX__;
        int costSum = 0;

        for (int i = sink; i != source; i = prev[i]) {
            add = std::min(add, getSpare(prev[i], i));
            costSum += cost[prev[i]][i];
        }
        for (int i = sink; i != source; i = prev[i]) {
            addFlow(prev[i], i, add);
        }

        result.flowed += add;
        result.cost += costSum * add;
    }

    return result;
}

struct Line {
    int axis, start, end, weight;

    Line(int a, int s, int e, int w) {
        axis = a;
        start = s;
        end = e;
        weight = w;
    }

    Line() : Line(0, 0, 0, 0) {}
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        std::vector<Line> horizontal, vertical;

        for (int i = 1; i <= n; ++i) {
            int x1, y1, x2, y2, w;
            scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
            if (x2 < x1) {
                std::swap(x1, x2);
            }
            horizontal.emplace_back(y1, x1, x2, w);
            addEdge(SRC, i, 0, 1);
        }

        for (int i = 1; i <= m; ++i) {
            int x1, y1, x2, y2, w;
            scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
            if (y2 < y1) {
                std::swap(y1, y2);
            }
            vertical.emplace_back(x1, y1, y2, w);
            addEdge(i+200, DST, 0, 1);
        }

        for (int i = 0; i < horizontal.size(); ++i) {
            for (int j = 0; j < vertical.size(); ++j) {
                Line& h = horizontal[i];
                Line& v = vertical[j];
                // (v.axis, h.axis) 에서 만나야 함.
                if (h.start <= v.axis && v.axis <= h.end &&
                    v.start <= h.axis && h.axis <= v.end) {
                    addEdge(i+1, j+1+200, -(h.weight*v.weight), 1);
                }
            }
        }

        auto result = MCMF(SRC, DST);
        printf("%d %d\n", result.flowed, -result.cost);

        std::fill(&capa[0][0], &capa[0][0] + sizeof(capa) / sizeof(int), 0);
        std::fill(&flow[0][0], &flow[0][0] + sizeof(flow) / sizeof(int), 0);
        std::fill(&cost[0][0], &cost[0][0] + sizeof(cost) / sizeof(int), 0);
    }

    return 0;
}