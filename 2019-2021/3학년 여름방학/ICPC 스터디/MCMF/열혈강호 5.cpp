#include <iostream>
#include <algorithm>
#include <queue>
#define INF ((__INT32_MAX__)/2)
#define SRC 801
#define DST 802
#define VERTEX_COUNT 803

int cost[VERTEX_COUNT][VERTEX_COUNT];
int flow[VERTEX_COUNT][VERTEX_COUNT];
int capa[VERTEX_COUNT][VERTEX_COUNT];
int prev[VERTEX_COUNT];
int dist[VERTEX_COUNT];
bool inQueue[VERTEX_COUNT];

void setCost(int src, int dst, int val) {
    cost[src][dst] = val;
    cost[dst][src] = -val;
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

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        int count;
        scanf("%d", &count);
        setCost(SRC, i, 0);
        capa[SRC][i] = 1;

        for (int j = 0; j < count; ++j) {
            int job, pay;
            scanf("%d %d", &job, &pay);
            setCost(i, 400+job, pay);
            capa[i][400+job] = 1;
        }
    }

    for (int i = 1; i <= m; ++i) {
        setCost(400+i, DST, 0);
        capa[400+i][DST] = 1;
    }

    auto result = MCMF(SRC, DST);
    printf("%d\n%d", result.flowed, result.cost);

    return 0;
}