#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        std::vector<int> count(31, 0);
        for (int i = 0; i < n; ++i) {
            int v;
            scanf("%d", &v);
            for (int i = 0; i < 31; ++i) {
                if (v&(1<<i)) {
                    count[i]++;
                }
            }
        }

        int result = 0;
        for (int i = 30; i >= 0; --i) {
            if (n-count[i] <= k) {
                k -= n-count[i];
                result += (1<<i);
            }
        }

        printf("%d\n", result);
    }

    return 0;
}