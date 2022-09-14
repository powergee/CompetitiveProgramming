#include <iostream>
#include <algorithm>
#include <vector>

using Edge = std::pair<int, int>;
using BCC = std::vector<Edge>;

class Graph {
private:
    int v, e, counter = 0;
    std::vector<std::vector<int>> graph;
    std::vector<int> visited, depth;
    std::vector<bool> isLucky, available;
    std::vector<BCC> bccs;
    std::vector<Edge> stack;

    int findBCCs(int start, int prev) {
        visited[start] = ++counter;
        int minReach = visited[start];

        for (int next : graph[start]) {
            if (next == prev) {
                continue;
            }
            if (visited[next] < visited[start]) {
                stack.emplace_back(start, next);
            }

            if (visited[next]) {
                minReach = std::min(minReach, visited[next]);
            } else {
                int nextMin = findBCCs(next, start);
                if (visited[start] <= nextMin) {
                    bccs.emplace_back();
                    while (!stack.empty()) {
                        auto[u, v] = stack.back();
                        stack.pop_back();
                        bccs.back().emplace_back(u, v);
                        if (std::min(u, v) == std::min(start, next) && 
                            std::max(u, v) == std::max(start, next)) {
                            break;
                        }
                    }
                }
                minReach = std::min(minReach, nextMin);
            }
        }

        return minReach;
    }

    bool hasOddCycle(int start, int currDepth) {
        depth[start] = currDepth;
        for (int next : graph[start]) {
            if (!available[next]) {
                continue;
            }
            if ((depth[next] == 0 && hasOddCycle(next, currDepth+1)) || 
                std::abs(depth[next]-currDepth) % 2 == 0) {
                return true;
            }
        }
        return false;
    }

public:
    Graph(int v, int e, std::vector<Edge> edges) {
        this->v = v;
        this->e = e;
        graph.resize(v);
        visited.resize(v, 0);
        depth.resize(v, 0);
        isLucky.resize(v, false);
        available.resize(v, false);
        for (Edge& edge : edges) {
            graph[edge.first-1].push_back(edge.second-1);
            graph[edge.second-1].push_back(edge.first-1);
        }
    }

    int countLuckyCities() {
        for (int i = 0; i < v; ++i) {
            if (visited[i] == 0) {
                findBCCs(i, -1);
            }
        }

        for (BCC& bcc : bccs) {
            for (Edge& edge : bcc) {
                available[edge.first] = true;
                available[edge.second] = true;
            }

            if (hasOddCycle(bcc.front().first, 1)) {
                for (Edge& edge : bcc) {
                    isLucky[edge.first] = true;
                    isLucky[edge.second] = true;
                }
            }

            for (Edge& edge : bcc) {
                available[edge.first] = false;
                available[edge.second] = false;
                depth[edge.first] = 0;
                depth[edge.second] = 0;
            }
        }

        int count = 0;
        for (int i = 0; i < v; ++i) {
            count += (isLucky[i] ? 1 : 0);
        }
        return count;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int v, e;
        std::vector<Edge> edges;
        scanf("%d %d", &v, &e);

        for (int i = 0; i < e; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            edges.emplace_back(a, b);
        }

        printf("%d\n", Graph(v, e, edges).countLuckyCities());
    }

    return 0;
}