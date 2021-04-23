#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> odd, even;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            if (val % 2) {
                odd.push_back(val);
            } else {
                even.push_back(val);
            }
        }

        for (int o : odd) {
            printf("%d ", o);
        }
        for (int e : even) {
            printf("%d ", e);
        }
        printf("\n");
    }

    return 0;
}