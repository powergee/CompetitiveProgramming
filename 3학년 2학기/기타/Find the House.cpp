#include <cstdio>
#include <map>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::map<Long, Long> edge;
    for (int i = 0; i < n; ++i) {
        Long start, dist;
        char dir[2];
        scanf("%lld %s %lld", &start, dir, &dist);
        edge[start] = start + (dir[0] == 'L' ? -dist : dist);
    }

    Long curr;
    scanf("%lld", &curr);
    while (edge.find(curr) != edge.end()) {
        curr = edge[curr];
    }

    printf("%lld", curr);
    return 0;
}
