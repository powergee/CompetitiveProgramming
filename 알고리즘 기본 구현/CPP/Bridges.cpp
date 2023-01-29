// Solution of 단절선(BOJ 11400)

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int main() {
    int v, e;
    scanf("%d %d", &v, &e);

    std::vector<std::vector<int>> graph(v+1);
    for (int i = 0; i < e; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int globalCount = 0;
    std::vector<int> visited(v+1, 0);
    std::vector<std::pair<int, int>> bridges;
    std::function<int(int, int)> getMinVisitTime = [&](int start, int parent) -> int {
        visited[start] = ++globalCount;
        int minTime = visited[start];
        for (int next : graph[start]) {
            if (next == parent) {
                continue;
            }
            if (visited[next] == 0) {
                int nextTime = getMinVisitTime(next, start);
                minTime = std::min(minTime, nextTime);
                if (visited[start] < nextTime) {
                    bridges.emplace_back(std::min(start, next), std::max(start, next));
                }
            } else {
                minTime = std::min(minTime, visited[next]);
            }
        }
        return minTime;
    };
    getMinVisitTime(1, 0);

    std::sort(bridges.begin(), bridges.end());
    printf("%d\n", (int)bridges.size());
    for (auto [a, b] : bridges) {
        printf("%d %d\n", a, b);
    }

    return 0;
}