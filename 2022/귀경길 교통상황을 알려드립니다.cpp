#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n+1);
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::vector<int> dist(n+1, -1);
    std::queue<int> q;
    dist[1] = 1;
    q.push(1);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (int next : graph[curr]) {
            if (dist[next] == -1) {
                dist[next] = dist[curr]+1;
                q.push(next);
            }
        }
    }

    std::vector<int> timetable(n+10, 0);
    for (int v = 1; v <= n; ++v) {
        int exist;
        std::cin >> exist;
        if (exist) {
            timetable[dist[v]]++;
        }
    }

    int lastOne = 0;
    for (size_t i = 1; i+1 < timetable.size(); ++i) {
        if (timetable[i] > 1) {
            timetable[i+1] += timetable[i]-1;
            timetable[i] = 1;
        }
        if (timetable[i]) {
            lastOne = i;
        }
    }

    std::cout << lastOne;

    return 0;
}