#include <iostream>
#include <queue>

typedef long long Long;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    std::priority_queue<Long, std::vector<Long>, std::greater<Long>> q;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        q.push(val);
    }

    while (k--) {
        Long v1 = q.top();
        q.pop();
        Long v2 = q.top();
        q.pop();
        q.push(v1+v2);
        q.push(v1+v2);
    }

    Long sum = 0;
    while (!q.empty()) {
        sum += q.top();
        q.pop();
    }

    printf("%lld", sum);
    return 0;
}