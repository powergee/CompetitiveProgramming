#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long l, r, a;
        scanf("%lld %lld %lld", &l, &r, &a);
        
        std::vector<Long> cands;

        cands.push_back((r/a) + (r%a));
        Long prevFloor = (r/a) - 1;
        Long prevFloorX = prevFloor * a + a - 1;
        if (l <= prevFloorX && prevFloorX <= r) {
            cands.push_back((prevFloorX/a) + (prevFloorX%a));
        }

        printf("%lld\n", *std::max_element(cands.begin(), cands.end()));
    }

    return 0;
}