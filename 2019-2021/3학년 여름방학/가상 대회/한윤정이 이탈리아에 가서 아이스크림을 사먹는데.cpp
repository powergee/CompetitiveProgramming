#include <iostream>
#include <set>

int main() {
    std::set<int> notAllowed[201];
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        notAllowed[u].insert(v);
        notAllowed[v].insert(u);
    }

    int count = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            for (int k = j+1; k <= n; ++k) {
                if (notAllowed[i].find(j) != notAllowed[i].end() ||
                    notAllowed[j].find(k) != notAllowed[j].end() ||
                    notAllowed[k].find(i) != notAllowed[k].end()) {
                    continue;
                }
                ++count;
            }
        }
    }

    printf("%d", count);

    return 0;
}