#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

std::vector<int> in[32001], out[32001];
int prevVisited[32001];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int prev, next;
        scanf("%d %d", &prev, &next);
        out[prev].push_back(next);
        in[next].push_back(prev);
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (int v = 1; v <= n; ++v) {
        if (in[v].empty()) {
            q.push(v);
        }
    }

    while (!q.empty()) {
        int curr = q.top();
        q.pop();
        printf("%d ", curr);
        
        for (int next : out[curr]) {
            prevVisited[next]++;
            if (prevVisited[next] == in[next].size()) {
                q.push(next);
            }
        }
    }

    return 0;
}