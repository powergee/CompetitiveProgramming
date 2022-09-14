#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

bool compare(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return p1.second > p2.second;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::map<int, int> count;
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);

            count[i+1] = val;
            total += val;
        }

        std::vector<std::pair<int, int>> pairs(count.begin(), count.end());
        std::sort(pairs.begin(), pairs.end(), compare);

        if ((int)pairs.size() == 1) {
            printf("majority winner %d\n", pairs.begin()->first);
        } else {
            auto first = pairs.front();
            auto second = *(pairs.begin()+1);

            if (first.second == second.second) {
                printf("no winner\n");
            } else if (first.second * 2 <= total) {
                printf("minority winner %d\n", first.first);
            } else {
                printf("majority winner %d\n", first.first);
            }
        }
    }

    return 0;
}