#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<std::pair<int, int>> range(q);
    std::vector<std::vector<int>> graph(n*2+2);
    for (int i = 0; i < q; ++i) {
        scanf("%d %d", &range[i].first, &range[i].second);
        graph[range[i].first*2].push_back(range[i].second*2+1);
        graph[range[i].second*2+1].push_back(range[i].first*2);
    }
    for (int i = 1; i < n; ++i) {
        graph[i*2+1].push_back((i+1)*2);
        graph[(i+1)*2].push_back(i*2+1);
    }

    std::vector<bool> visited(n*2+1, false);
    std::queue<int> bfsQ;
    bfsQ.push(1*2);
    visited[1*2] = true;
    bool found = false;

    while (!bfsQ.empty()) {
        int curr = bfsQ.front();
        bfsQ.pop();
        if (curr == n*2+1) {
            found = true;
            break;
        }
        for (int next : graph[curr]) {
            if (!visited[next]) {
                visited[next] = true;
                bfsQ.push(next);
            }
        }
    }
    
    if (found) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}