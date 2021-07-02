#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
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

void enqueue(int next, int dist, int prev, bool* visited, int* prevArr, std::queue<State>& q) {
    if (isAvailable(next, visited)) {
        q.emplace(next, dist);
        if (prevArr[next] == -1) {
            prevArr[next] = prev;
        }
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int minDist = __INT32_MAX__;
    bool* visited = new bool[UPPER_BOUND+1];
    int* prev = new int[UPPER_BOUND+1];
    std::fill(visited, visited+UPPER_BOUND+1, false);
    std::fill(prev, prev+UPPER_BOUND+1, -1);
    std::queue<State> q;
    q.emplace(n, 0);

    while (!q.empty()) {
        State now = q.front();
        q.pop();
        visited[now.pos] = true;

        if (now.pos == k) {
            minDist = now.dist;
            break;
        } else {
            enqueue(now.pos+1, now.dist+1, now.pos, visited, prev, q);
            enqueue(now.pos-1, now.dist+1, now.pos, visited, prev, q);
            enqueue(now.pos*2, now.dist+1, now.pos, visited, prev, q);
        }
    }

    printf("%d\n", minDist);
    std::stack<int> s;
    for (int p = k; p != -1; p = prev[p]) {
        s.push(p);
    }
    while (!s.empty()) {
        printf("%d ", s.top());
        s.pop();
    }

    return 0;
}