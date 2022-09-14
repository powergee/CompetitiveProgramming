#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main() {
    int n, m;
    scanf("%d", &n);

    std::vector<int> crane(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &crane[i]);
    }
    int maxCrane = *std::max_element(crane.begin(), crane.end());

    scanf("%d", &m);
    std::multiset<int> boxes;
    for (int i = 0; i < m; ++i) {
        int size;
        scanf("%d", &size);
        boxes.insert(size);
    }

    if (boxes.upper_bound(maxCrane) == boxes.end()) {
        int time = 0;
        while (!boxes.empty()) {
            ++time;
            for (int c : crane) {
                if (boxes.empty()) {
                    break;
                }
                auto bound = boxes.upper_bound(c);
                if (bound != boxes.begin()) {
                    auto moving = std::prev(bound);
                    boxes.erase(moving);
                }
            }
        }
        printf("%d", time);
    } else {
        printf("-1");
    }

    return 0;
}
