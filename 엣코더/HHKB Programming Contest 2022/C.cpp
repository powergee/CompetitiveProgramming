#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<int> arr(n);
    std::map<int, std::vector<int>> buckets;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        buckets[arr[i]].emplace_back(i);
    }

    while (q--) {
        int x, k;
        scanf("%d %d", &x, &k);

        if (buckets[x].size() < k) {
            printf("-1\n");
        } else {
            printf("%d\n", buckets[x][k-1]+1);
        }
    }

    return 0;
}