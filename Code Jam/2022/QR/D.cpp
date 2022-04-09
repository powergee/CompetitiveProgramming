#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef long long Long;

struct Flow {
    int endpoint;
    Long maxValue;
};

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        int n;
        scanf("%d", &n);

        std::vector<Long> value(n+1);
        std::vector<int> next(n+1), indegree(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &value[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &next[i]);
            indegree[next[i]]++;
        }

        std::queue<Flow> q;
        std::vector<std::vector<Flow>> inJunc(n+1);
        for (int i = 1; i <= n; ++i) {
            if (indegree[i] == 0) {
                q.push({i, value[i]});
            }
        }

        Long answer = 0;
        while (!q.empty()) {
            Flow curr = q.front();
            q.pop();
            int nextEnd = next[curr.endpoint];

            if (nextEnd) {
                inJunc[nextEnd].push_back(curr);
                indegree[nextEnd]--;

                if (indegree[nextEnd] == 0) {
                    std::sort(inJunc[nextEnd].begin(), inJunc[nextEnd].end(), [](Flow f1, Flow f2) {
                        return f1.maxValue < f2.maxValue;
                    });
                    q.push({
                        nextEnd,
                        std::max(inJunc[nextEnd][0].maxValue, value[nextEnd])
                    });
                    for (int i = 1; i < inJunc[nextEnd].size(); ++i) {
                        answer += inJunc[nextEnd][i].maxValue;
                    }
                    inJunc[nextEnd].clear();
                }
            } else {
                answer += curr.maxValue;
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}