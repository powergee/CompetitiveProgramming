#include <iostream>
#include <set>

int order[100];
int dist[101][100];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; ++i) {
        scanf("%d", order+i);
    }

    for (int i = 1; i <= k; ++i) {
        dist[i][k-1] = (order[k-1] == i ? 0 : 1);
        for (int j = k-2; j >= 0; --j) {
            dist[i][j] = (order[j] == i ? 0 : dist[i][j+1]+1);
        }
    }

    int missCount = 0;
    std::set<int> cache;
    for (int i = 0; i < k; ++i) {
        if (cache.find(order[i]) == cache.end()) {
            if (cache.size() == n) {
                int maxDist = INT32_MIN;
                int maxDistItem = -1;
                for (int item : cache) {
                    if (maxDist < dist[item][i]) {
                        maxDist = dist[item][i];
                        maxDistItem = item;
                    }
                }
                cache.erase(maxDistItem);
                cache.insert(order[i]);
                ++missCount;
            } else {
                cache.insert(order[i]);
            }
        }
    }

    printf("%d", missCount);

    return 0;
}