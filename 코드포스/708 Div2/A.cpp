#include <iostream>
#include <map>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::map<int, int> count;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            count[val] += 1;
        }

        for (auto p : count) {
            printf("%d ", p.first);
        }

        for (auto p : count) {
            int iter = p.second - 1;
            for (int i = 0; i < iter; ++i) {
                printf("%d ", p.first);
            }
        }

        printf("\n");
    }

    return 0;
}