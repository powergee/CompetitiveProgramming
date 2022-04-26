#include <iostream>
#include <vector>
#include <queue>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n, k;
        scanf("%lld %lld", &n, &k);

        std::vector<Long> problems(n);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &problems[i]);
        }

        std::priority_queue<std::pair<Long, int>, std::vector<std::pair<Long, int>>, std::greater<std::pair<Long, int>>> q;
        std::vector<Long> solved;
        
        for (int i = 0; i < n; i += 2) {
            q.emplace(problems[i], i);
            if (i+1 < n) {
                q.emplace(problems[i+1], i+1);
            }
            if (q.top().first <= k) {
                k -= q.top().first;
                solved.push_back(q.top().second+1);
                q.pop();
            } else {
                break;
            }
        }
        
        while (!q.empty() && q.top().first <= k) {
            k -= q.top().first;
            solved.push_back(q.top().second+1);
            q.pop();
        }

        printf("%d\n", (int)solved.size());
        for (int v : solved) {
            printf("%d ", v);
        }
        printf("\n");
    }

    return 0;
}