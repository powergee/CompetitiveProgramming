#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<int>> pos(n+1);
    for (int i = 0; i < n; ++i) {
        int x;
        scanf("%d", &x);
        pos[x].push_back(i+1);
    }

    int q;
    scanf("%d", &q);
    
    while (q--) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        auto left = std::lower_bound(pos[x].begin(), pos[x].end(), l);
        auto right = std::upper_bound(pos[x].begin(), pos[x].end(), r);
        printf("%d\n", int(right-left));
    }

    return 0;
}