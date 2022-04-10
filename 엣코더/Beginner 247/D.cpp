#include <iostream>
#include <deque>

typedef long long Long;

int main() {
    int q;
    scanf("%d", &q);

    std::deque<std::pair<Long, Long>> cylinder;
    while (q--) {
        int comm;
        scanf("%d", &comm);
        
        if (comm == 1) {
            Long x, c;
            scanf("%lld %lld", &x, &c);
            cylinder.emplace_back(x, c);
        } else {
            Long c;
            scanf("%lld", &c);
            Long sum = 0;
            
            while (c) {
                auto front = cylinder.front();
                cylinder.pop_front();
                if (front.second <= c) {
                    sum += front.first * front.second;
                    c -= front.second;
                } else {
                    sum += front.first * c;
                    front.second -= c;
                    cylinder.push_front(front);
                    c = 0;
                }
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}