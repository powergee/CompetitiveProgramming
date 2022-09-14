#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

using Long = long long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<std::vector<Long>> edges(n);
    Long patrol = 0;
    for (int i = 0; i < n-1; ++i) {
        int u, v;
        Long p;
        scanf("%d %d %lld", &u, &v, &p);
        edges[u].push_back(p);
        edges[v].push_back(p);
        patrol += p;
    }

    for (int i = 0; i < n; ++i) {
        Long sum = std::accumulate(edges[i].begin(), edges[i].end(), 0LL);
        Long max = *std::max_element(edges[i].begin(), edges[i].end());
        Long spare = sum - max;

        Long unmatched;
        if (max < spare) {
            unmatched = (sum % 2 == 0 ? 0LL : 1LL);
        } else {
            unmatched = max - spare;
        }
        Long matched = sum - unmatched;
        patrol -= matched / 2;
    }

    printf("%lld", patrol);
    return 0;
}
