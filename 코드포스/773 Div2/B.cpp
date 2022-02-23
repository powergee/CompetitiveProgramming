#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> powerUp(n);
        std::map<int, int> count;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &powerUp[i]);
            count[powerUp[i]]++;
        }

        for (int i = 0; i < count.size(); ++i) {
            printf("%d ", int(count.size()));
        }
        for (int i = count.size(); i < n; ++i) {
            printf("%d ", i+1);
        }
        printf("\n");
    }

    return 0;
}