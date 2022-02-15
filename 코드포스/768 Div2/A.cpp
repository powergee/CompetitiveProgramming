#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &b[i]);
        }

        for (int i = 0; i < n; ++i) {
            if (a[i] < b[i]) {
                std::swap(a[i], b[i]);
            }
        }

        printf("%d\n", *std::max_element(a.begin(), a.end()) * *std::max_element(b.begin(), b.end()));
    }

    return 0;
}