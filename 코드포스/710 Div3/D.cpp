#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        std::map<int, int> count;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            count[val]++;
        }
        
        std::priority_queue<int> q;
        for (auto c : count) {
            q.push(c.second);
        }

        while (q.size() >= 2) {
            int m1 = q.top();
            q.pop();
            int m2 = q.top();
            q.pop();

            --m1, --m2;
            if (m1) {
                q.push(m1);
            }
            if (m2) {
                q.push(m2);
            }
        }

        if (q.empty()) {
            printf("0\n");
        } else {
            printf("%d\n", q.top());
        }
    }
}