#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> seminars(10001);

    for (int i = 0; i < n; ++i) {
        int p, d;
        scanf("%d %d", &p, &d);
        seminars[d].push_back(p);
    }

    int answer = 0;
    std::priority_queue<int> q;
    for (int i = 10000; i > 0; --i) {
        for (int s : seminars[i]) {
            q.push(s);
        }

        if (!q.empty()) {
            answer += q.top();
            q.pop();
        }
    }

    printf("%d", answer);

    return 0;
}