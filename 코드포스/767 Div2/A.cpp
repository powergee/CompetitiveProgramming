#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<std::pair<int, int>> soft(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &soft[i].first);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &soft[i].second);
        }

        std::sort(soft.begin(), soft.end());
        for (int i = 0; i < n; ++i) {
            if (k < soft[i].first) {
                break;
            }
            k += soft[i].second;
        }

        printf("%d\n", k);
    }

    return 0;
}