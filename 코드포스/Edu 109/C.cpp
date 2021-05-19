#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

struct Robot {
    int pos, time;
    char dir;
};

bool comparePos(const Robot* r1, const Robot* r2) {
    return r1->pos < r2->pos;
}

void fillTimes(std::vector<Robot*> robots, int bound) {
    std::sort(robots.begin(), robots.end(), comparePos);

    std::stack<Robot*> s;
    for (Robot* r : robots) {
        if (s.empty()) {
            s.push(r);
        } else if (s.top()->dir == 'R') {
            if (r->dir == 'R') {
                s.push(r);
            } else {
                Robot* prev = s.top();
                s.pop();
                int time = (r->pos - prev->pos) / 2;
                prev->time = time;
                r->time = time;
            }
        } else if (s.top()->dir == 'L') {
            if (r->dir == 'R') {
                s.push(r);
            } else {
                Robot* prev = s.top();
                s.pop();
                int time = (r->pos + prev->pos) / 2;
                prev->time = time;
                r->time = time;
            }
        }
    }

    while (s.size() > 1) {
        Robot* right = s.top();
        s.pop();
        Robot* left = s.top();
        s.pop();

        if (left->dir == 'R' && right->dir == 'R') {
            int time = bound - (left->pos + right->pos) / 2;
            left->time = time;
            right->time = time;
        } else {
            int time = bound + (left->pos - right->pos) / 2;
            left->time = time;
            right->time = time;
        }
    }

    if (!s.empty()) {
        Robot* inf = s.top();
        s.pop();
        inf->time = -1;
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        std::vector<Robot> all;
        std::vector<Robot*> odd, even;
        for (int i = 0; i < n; ++i) {
            Robot r;
            scanf("%d", &r.pos);
            all.push_back(r);
        }

        for (int i = 0; i < n; ++i) {
            scanf("%s", &all[i].dir);
        }

        for (Robot& r : all) {
            if (r.pos % 2 == 0) {
                even.push_back(&r);
            } else {
                odd.push_back(&r);
            }
        }

        fillTimes(even, m);
        fillTimes(odd, m);

        for (int i = 0; i < n; ++i) {
            printf("%d ", all[i].time);
        }
        printf("\n");
    }

    return 0;
}