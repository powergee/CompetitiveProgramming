#include <iostream>
#include <algorithm>
#include <vector>

int v, e, counter = 0;
std::vector<int> graph[10000];
int visited[10000];
bool isArtic[10000];

int findMinReachable(int start, bool isRoot) {
    visited[start] = ++counter;
    int minReach = visited[start];
    int childCount = 0;

    for (int next : graph[start]) {
        if (visited[next]) {
            minReach = std::min(minReach, visited[next]);
        } else {
            ++childCount;
            int nextMin = findMinReachable(next, false);
            if (visited[start] <= nextMin) {
                isArtic[start] = true;
            }
            minReach = std::min(minReach, nextMin);
        }
    }

    if (isRoot) {
        isArtic[start] = (2 <= childCount);
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
            findMinReachable(i, true);
        }
    }

    for (int i = 0; i < v; ++i) {
        articCount += (isArtic[i] ? 1 : 0);
    }
    
    printf("%d\n", articCount);
    for (int i = 0; i < v; ++i) {
        if (isArtic[i]) {
            printf("%d ", i+1);
        }
    }

    return 0;
}