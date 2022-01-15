#include <iostream>
#include <queue>
#include <vector>
#include <string>

typedef long long Long;
const Long MAX_RANGE = Long(1e7);

Long pow10(int e) {
    Long result = 1;
    for (int i = 0; i < e; ++i) {
        result *= 10;
    }
    return result;
}

int main() {
    Long a, n;
    scanf("%lld %lld", &a, &n);

    std::vector<bool> visited(MAX_RANGE, false);
    std::queue<std::pair<Long, int>> q;
    q.emplace(1LL, 0);
    
    while (!q.empty()) {
        auto p = q.front();
        q.pop();

        if (p.first == n) {
            printf("%d", p.second);
            return 0;
        }

        Long mult = p.first * a;
        if (mult < MAX_RANGE && !visited[mult]) {
            q.emplace(mult, p.second+1);
            visited[mult] = true;
        }
        if (p.first >= 10 && p.first % 10 != 0) {
            Long shifted = (p.first / 10) + (p.first % 10) * pow10(std::to_string(p.first).size()-1);
            if (shifted < MAX_RANGE && !visited[shifted]) {
                q.emplace(shifted, p.second+1);
                visited[shifted] = true;
            }
        }
    }

    printf("-1");

    return 0;
}