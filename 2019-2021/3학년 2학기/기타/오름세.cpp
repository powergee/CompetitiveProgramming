#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        std::vector<int> ascending;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            auto found = std::lower_bound(ascending.begin(), ascending.end(), val);
            if (found == ascending.end()) {
                ascending.push_back(val);
            } else {
                *found = val;
            }
        }
        printf("%d\n", (int)ascending.size());
    }

    return 0;
}