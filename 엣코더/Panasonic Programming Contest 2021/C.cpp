#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, q;
    std::scanf("%d %d", &n, &q);

    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        int h;
        scanf("%d", &h);
        heights[i] = h;
    }

    std::sort(heights.begin(), heights.end());
    for (int i = 0; i < q; ++i) {
        int x;
        scanf("%d", &x);
        auto found = std::lower_bound(heights.begin(), heights.end(), x);
        printf("%ld\n", n - (found - heights.begin()));
    }

    return 0;
}
