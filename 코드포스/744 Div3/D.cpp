#include <iostream>
#include <queue>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::priority_queue<std::pair<int, int>> q;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            if (val > 0) {
                q.emplace(val, i+1);
            }
        }

        std::vector<std::pair<int, int>> answer;
        while (q.size() > 1) {
            auto p1 = q.top();
            q.pop();
            auto p2 = q.top();
            q.pop();

            answer.emplace_back(p1.second, p2.second);
            p1.first--;
            p2.first--;
            
            if (p1.first) {
                q.push(p1);
            }
            if (p2.first) {
                q.push(p2);
            }
        }

        printf("%d\n", (int)answer.size());
        for (auto p : answer) {
            printf("%d %d\n", p.first, p.second);
        }
    }

    return 0;
}