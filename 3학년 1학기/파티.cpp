#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

struct Context {
    int pos, time;
    Context(int pos, int time) : pos(pos), time(time) {}
};

struct ContextComparer {
    bool operator()(const Context& c1, const Context& c2) const {
        return c1.time > c2.time;
    }
};

int n, m, x;
std::vector<std::pair<int, int>> original[1001];
std::vector<std::pair<int, int>> opposite[1001];
int originalDist[1001];
int oppositeDist[1001];

void fillDist(int* dist, std::vector<std::pair<int, int>>* graph) {
    std::fill(dist + 1, dist + n + 1, 1000001);
    dist[x] = 0;
    std::priority_queue<Context, std::vector<Context>, ContextComparer> q;
    q.emplace(x, 0);

    while (!q.empty()) {
        auto now = q.top();
        q.pop();

        for (auto next : graph[now.pos]) {
            int newTime = now.time + next.second;
            if (newTime < dist[next.first]) {
                dist[next.first] = newTime;
                q.emplace(next.first, newTime);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &x);

    for (int i = 0; i < m; ++i) {
        int s, e, t;
        scanf("%d %d %d", &s, &e, &t);
        original[s].emplace_back(e, t);
        opposite[e].emplace_back(s, t);
    }

    fillDist(originalDist, original);
    fillDist(oppositeDist, opposite);

    int result = -1;
    for (int v = 1; v <= n; ++v) {
        result = std::max(result, originalDist[v] + oppositeDist[v]);
    }

    printf("%d", result);

    return 0;
}