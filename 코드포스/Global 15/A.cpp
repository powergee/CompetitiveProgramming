#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        char str[41];
        char sorted[41];
        scanf("%d", &n);
        scanf("%s", str);
        std::copy(str, str+n, sorted);
        std::sort(sorted, sorted+n);
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (str[i] != sorted[i]) {
                ++count;
            }
        }
        printf("%d\n", count);
    }

    return 0;
}