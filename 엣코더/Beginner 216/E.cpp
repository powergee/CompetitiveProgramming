#include <iostream>
#include <vector>
#include <map>

typedef long long Long;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::map<Long, Long, std::greater<Long>> funCount;
    funCount[0] = 0;
    for (int i = 0; i < n; ++i) {
        Long fun;
        scanf("%lld", &fun);
        funCount[fun]++;
    }

    Long total = 0;
    while (k > 0 && funCount.size() > 1) {
        auto curr = *funCount.begin();
        auto next = *std::next(funCount.begin());

        if ((curr.first - next.first) * curr.second <= k) {
            Long segCount = curr.first-next.first;
            total += curr.first*curr.second*segCount - curr.second*segCount*(segCount-1)/2;
            k -= (curr.first - next.first) * curr.second;
        } else {
            Long segCount = k/curr.second;
            total += curr.first*curr.second*segCount - curr.second*segCount*(segCount-1)/2;
            total += (curr.first - k/curr.second) * (k - curr.second * (k/curr.second));
            k = 0;
        }

        funCount.erase(funCount.begin());
        funCount[next.first] += curr.second;
    }

    printf("%lld", total);

    return 0;
}