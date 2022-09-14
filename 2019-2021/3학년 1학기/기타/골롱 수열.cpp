#include <iostream>
#include <deque>

using Long = long long;

int main() {
    Long n;
    scanf("%lld", &n);
    std::deque<std::pair<Long, Long>> d;
    d.emplace_back(1, 1);
    int count = 0;
    Long ac = 0;

    while (ac < n) {
        ++count;
        auto now = d.front();
        ac += now.second;
        d.emplace_back(ac, count);
        if (d[1].first <= count) {
            d.pop_front();
        }
    }

    if (d.back().first <= n) {
        printf("%lld", d.back().second);
    } else {
        printf("%lld", d[d.size()-2].second);
    }

    return 0;
}