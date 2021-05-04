#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <climits>

int main(){
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m, x;
        scanf("%d %d %d", &n, &m, &x);
        std::vector<std::pair<int, int>> blocks(n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &blocks[i].first);
            blocks[i].second = i;
        }

        std::sort(blocks.begin(), blocks.end(), std::greater<std::pair<int, int>>());
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
        std::vector<int> answer(n);
        for (int i = 0; i < m; ++i) {
            q.emplace(0, i);
        }

        for (auto block : blocks) {
            auto place = q.top();
            q.pop();
            place.first += block.first;
            q.push(place);

            answer[block.second] = place.second;
        }

        int min, max;
        min = max = q.top().first;
        for (int i = 0; i < n; ++i) {
            auto curr = q.top();
            q.pop();
            min = std::min(min, curr.first);
            max = std::max(max, curr.first);
        }

        if (max - min > x) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for (int v : answer) {
                printf("%d ", v+1);
            }
            printf("\n");
        }
    }

    return 0;
}