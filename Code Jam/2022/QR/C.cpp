#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        int n;
        scanf("%d", &n);
        std::vector<int> dices(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &dices[i]);
        }

        std::sort(dices.begin(), dices.end());
        int built = 0;
        for (int d : dices) {
            if (built+1 <= d) {
                ++built;
            }
        }

        printf("%d\n", built);
    }
    
    return 0;
}