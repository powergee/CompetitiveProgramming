#include <iostream>
#include <deque>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::deque<int> result;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            if (result.empty() || val < result.front()) {
                result.push_front(val);
            } else {
                result.push_back(val);
            }
        }

        for (int val : result) {
            printf("%d ", val);
        }
        printf("\n");
    }

    return 0;
}