#include <iostream>
#include <algorithm>
#include <queue>
#define UPPER_BOUND 100000

struct State {
    int pos, dist;

    State(int p, int d) {
        pos = p;
        dist = d;
    }
};

bool isAvailable(int pos, bool* visited) {
    return 0 <= pos && pos <= UPPER_BOUND && !visited[pos];
}

void enqueue(int pos, int dist, bool* visited, std::queue<State>& q) {
    if (isAvailable(pos, visited)) {
        q.emplace(pos, dist);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int minDist = __INT32_MAX__;
    int cases = 0;
    bool* visited = new bool[UPPER_BOUND+1];
    std::fill(visited, visited+UPPER_BOUND+1, false);
    std::queue<State> q;
    q.emplace(n, 0);

    while (!q.empty()) {
        State now = q.front();
        q.pop();
        visited[now.pos] = true;

        if (now.pos == k) {
            if (minDist == __INT32_MAX__) {
                minDist = now.dist;
            }
            if (minDist == now.dist) {
                ++cases;
            }
        } else {
            enqueue(now.pos+1, now.dist+1, visited, q);
            enqueue(now.pos-1, now.dist+1, visited, q);
            enqueue(now.pos*2, now.dist+1, visited, q);
        }
    }

    printf("%d\n%d", minDist, cases);

    return 0;
}