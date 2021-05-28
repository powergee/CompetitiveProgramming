#include <iostream>
#include <queue>
#include <numeric>

typedef long long Long;

int main() {
    int n;
    std::priority_queue<Long, std::vector<Long>, std::greater<Long>> q;
    scanf("%d", &n);

    int answer = 0;
    Long hp = 0;
    for (int i = 0; i < n; ++i) {
        Long val;
        scanf("%lld", &val);
        if (val >= 0) {
            hp += val;
            ++answer;
        } else if (hp + val >= 0) {
            hp += val;
            q.push(val);
        } else if (!q.empty() && q.top() < val) {
            hp -= q.top();
            hp += val;
            q.pop();
            q.push(val);
        }
    }

    printf("%d", answer + (int)q.size());
    
    return 0;
}