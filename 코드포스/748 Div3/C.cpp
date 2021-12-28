#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<int> mice(k);
        for (int i = 0; i < k; ++i) {
            scanf("%d", &mice[i]);
        }
        std::sort(mice.begin(), mice.end(), std::greater<int>());

        int count = 0;
        int sum = 0;
        for (int i = 0; i < k; ++i) {
            sum += (n-mice[i]);
            if (n <= sum) {
                break;
            } else {
                ++count;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}