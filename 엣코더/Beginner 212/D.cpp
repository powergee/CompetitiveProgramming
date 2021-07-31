#include <iostream>
#include <algorithm>
#include <queue>

using Long = long long;

int main() {
    int q;
    scanf("%d", &q);
    Long plus = 0;
    std::priority_queue<Long, std::vector<Long>, std::greater<Long>> bag;

    for (int i = 0; i < q; ++i) {
        int type;
        Long x;
        scanf("%d", &type);

        switch (type)
        {
        case 1:
            scanf("%lld", &x);
            bag.push(x-plus);
            break;
        
        case 2:
            scanf("%lld", &x);
            plus += x;
            break;

        case 3:
            printf("%lld\n", bag.top()+plus);
            bag.pop();
            break;
        }
    }
}