#include <iostream>
#include <vector>
#include <queue>
#include <set>

struct State {
    int time, pressed;
    bool started;

    State(int t, int p, bool s) {
        time = t;
        pressed = p;
        started = s;
    }
};

int main() {
    int m, s;
    scanf("%d:%d", &m, &s);

    int goal = m*60 + s;
    std::set<std::pair<int, bool>> visited;
    std::queue<State> q;
    
    q.emplace(0, 0, false);
    visited.emplace(0, false);

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        if (curr.time == goal && curr.started) {
            printf("%d", curr.pressed);
            break;
        }

        auto tryToEmplace = [&](int time, int pressed, bool started) -> void {
            if (time <= goal && visited.find({time, started}) == visited.end()) {
                q.emplace(time, pressed, started);
                visited.emplace(time, started);
            }
        };

        for (int add : {10, 60, 600}) {
            tryToEmplace(curr.time+add, curr.pressed+1, curr.started);
        }
        if (curr.started) {
            tryToEmplace(curr.time+30, curr.pressed+1, curr.started);
        } else {
            tryToEmplace(curr.time == 0 ? 30 : curr.time, curr.pressed+1, true);
        }
    }

    return 0;
}