#include <iostream>
#include <string>
#include <vector>
#include <numeric>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        std::vector<int> ink(4, INT32_MAX);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                int amount;
                scanf("%d", &amount);
                ink[j] = std::min(ink[j], amount);
            }
        }
        if (std::accumulate(ink.begin(), ink.end(), 0) < 1000000) {
            printf("IMPOSSIBLE\n");
        } else {
            int used = 0;
            for (int i = 0; i < 4; ++i) {
                int currUsing = std::min(1000000-used, ink[i]);
                printf("%d ", currUsing);
                used += currUsing;
            }
            printf("\n");
        }
    }
    
    return 0;
}