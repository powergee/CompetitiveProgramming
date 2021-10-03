#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k, totalXOR = 0;
        scanf("%d %d", &n, &k);

        std::vector<int> value(n+1);
        std::vector<std::vector<int>> tree(n+1);

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &value[i]);
            totalXOR ^= value[i];
        }
        for (int i = 0; i < n-1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        if (totalXOR == 0) {
            printf("YES\n");
        } else if (k > 2) {
            std::vector<bool> visited(n+1, false);
            int count = 0;

            std::function<int(int)> getXOR;
            getXOR = [&](int start) -> int {
                visited[start] = true;

                int sum = value[start];
                for (int next : tree[start]) {
                    if (!visited[next]) {
                        sum ^= getXOR(next);
                    }
                }
                if (sum == totalXOR) {
                    ++count;
                    return 0;
                }
                return sum;
            };
            getXOR(1);

            if (count >= 2) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        } else {
            printf("NO\n");
        }
    }

    return 0;
}