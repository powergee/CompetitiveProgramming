#include <iostream>
#include <algorithm>
#include <queue>

int edges[101];
bool visited[101];

struct State {
    int pos, steps;

    State(int p, int s) {
        pos = p;
        steps = s;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n+m; ++i) {
        int from, to;
        scanf("%d %d", &from, &to);
        edges[from] = to;
    }

    std::queue<State> q;
    q.emplace(1, 0);

    while (!q.empty()) {
        auto now = q.front();
        q.pop();

        if (visited[now.pos]) {
            continue;
        }
        visited[now.pos] = true;

        if (now.pos == 100) {
            printf("%d", now.steps);
            break;
        }

        for (int i = now.pos+1; i <= std::min(now.pos+6, 100); ++i) {
            if (!visited[i]) {
                if (edges[i]) {
                    q.emplace(edges[i], now.steps + 1);
                } else {
                    q.emplace(i, now.steps + 1);
                }
            }
        }
    }
}