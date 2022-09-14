#include <iostream>
#include <queue>

typedef long long Long;

int main() {
    Long a, b;
    scanf("%lld %lld", &a, &b);

    std::queue<std::pair<Long, int>> q;
    q.emplace(a, 1);
    int answer = -1;
    
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        if (b == curr.first) {
            answer = curr.second;
            break;
        } else if (b < curr.first) {
            continue;
        }

        q.emplace(curr.first*2, curr.second+1);
        q.emplace(curr.first*10+1, curr.second+1);
    }

    printf("%d", answer);

    return 0;
}