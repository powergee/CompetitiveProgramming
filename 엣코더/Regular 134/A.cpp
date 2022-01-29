#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    Long n, l, w;
    scanf("%lld %lld %lld", &n, &l, &w);

    std::vector<Long> tarps(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &tarps[i]);
    }

    Long pos = 0, answer = 0;
    for (int i = 0; i < n; ++i) {
        Long left = tarps[i];
        Long right = left+w;
        if (pos < left) {
            Long toFill = left-pos;
            answer += toFill / w + (toFill % w ? 1 : 0);
        }
        pos = std::max(pos, right);
    }
    if (pos < l) {
        Long toFill = l-pos;
        answer += toFill / w + (toFill % w ? 1 : 0);
    }

    printf("%lld", answer);

    return 0;
}