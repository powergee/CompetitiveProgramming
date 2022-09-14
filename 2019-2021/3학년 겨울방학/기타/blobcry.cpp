#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

struct Edge {
    int a, b;
    bool isBridge;
    bool counted;
};

int main() {
    int v, e;
    scanf("%d %d", &v, &e);

    std::vector<Edge> edges(e);
    std::vector<std::vector<Edge*>> graph(v+1);
    for (int i = 0; i < e; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[i] = { a, b, false, false };
        graph[a].push_back(&edges[i]);
        graph[b].push_back(&edges[i]);
    }

    if (e % 2 == 0) {
        printf("0");
        return 0;
    }

    int globalCount = 0;
    std::vector<int> edgeCount(v+1, 0);
    std::vector<int> visited(v+1, 0);
    std::function<int(int, int)> getMinVisitTime = [&](int start, int parent) -> int {
        edgeCount[start] = 0;
        visited[start] = ++globalCount;
        int minTime = visited[start];

        for (auto edge : graph[start]) {
            int next = (edge->a == start ? edge->b : edge->a);
            if (next == parent) {
                continue;
            }
            edgeCount[start] += edge->counted ? 0 : 1;
            edge->counted = true;
            if (visited[next] == 0) {
                int nextTime = getMinVisitTime(next, start);
                minTime = std::min(minTime, nextTime);
                if (visited[start] < nextTime) {
                    edge->isBridge = true;
                }
                edgeCount[start] += edgeCount[next];
            } else {
                minTime = std::min(minTime, visited[next]);
            }
        }
        return minTime;
    };
    getMinVisitTime(1, 0);

    std::vector<int> answer;
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i].isBridge) {
            int comp1 = std::min(edgeCount[edges[i].a], edgeCount[edges[i].b]);
            int comp2 = e - comp1 - 1;
            if (comp1 % 2 == 0 && comp2 % 2 == 0) {
                answer.push_back(i+1);
            }
        } else {
            answer.push_back(i+1);
        }
    }

    printf("%d\n", (int)answer.size());
    for (int ans : answer) {
        printf("%d ", ans);
    }

    return 0;
}