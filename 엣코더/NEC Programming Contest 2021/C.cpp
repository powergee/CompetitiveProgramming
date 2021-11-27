#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, w;
    scanf("%d %d", &n, &w);
    std::vector<std::pair<int, int>> cheeses(n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &cheeses[i].first, &cheeses[i].second);
    }

    std::sort(cheeses.begin(), cheeses.end(), [](std::pair<int, int> c1, std::pair<int, int> c2) -> bool {
        return c1.first > c2.first;
    });

    long long total = 0;
    for (int i = 0; i < n && w > 0; ++i) {
        int toUse = std::min(w, cheeses[i].second);
        total += (long long)toUse * cheeses[i].first;
        w -= toUse;
    }

    printf("%lld", total);

    return 0;
}
