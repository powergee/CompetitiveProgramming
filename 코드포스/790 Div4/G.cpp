#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<std::vector<int>> child(n+1, std::vector<int>());
        for (int i = 2; i <= n; ++i) {
            int j;
            scanf("%d", &j);
            child[j].push_back(i);
        }

        char color[n+2];
        scanf("%s", color+1);

        int answer = 0;
        std::function<std::pair<int, int>(int)> countColors = [&](int start) -> std::pair<int, int> {
            std::pair<int, int> total = { 0, 0 };
            if (color[start] == 'W') {
                total.first++;
            } else {
                total.second++;
            }

            for (int next : child[start]) {
                auto sub = countColors(next);
                total.first += sub.first;
                total.second += sub.second;
            }

            if (total.first == total.second) {
                ++answer;
            }
            return total;
        };
        countColors(1);
        printf("%d\n", answer);
    }

    return 0;
}