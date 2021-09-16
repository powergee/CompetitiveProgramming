#include <iostream>
#include <algorithm>
#include <vector>

int v, e, counter = 0;
std::vector<int> graph[100000];
int visited[100000];
std::vector<std::pair<int, int>> bridges;

int findMinReachable(int start, int parent) {
    visited[start] = ++counter;
    int minReach = visited[start];

    for (int next : graph[start]) {
        if (next == parent) {
            continue;
        }
        if (visited[next]) {
            minReach = std::min(minReach, visited[next]);
        } else {
            int nextMin = findMinReachable(next, start);
            if (visited[start] < nextMin) {
                bridges.emplace_back(std::min(start, next), std::max(start, next));
            }
            minReach = std::min(minReach, nextMin);
        }
    }
    return minReach;
}

int main() {
    scanf("%d %d", &v, &e);
    for (int i = 0; i < e; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }
    
    int articCount = 0;
    for (int i = 0; i < v; ++i) {
        if (visited[i] == 0) {
            findMinReachable(i, -1);
        }
    }

    std::sort(bridges.begin(), bridges.end());

    printf("%d\n", (int)bridges.size());
    for (auto b : bridges) {
        printf("%d %d\n", b.first+1, b.second+1);
    }

    return 0;
}