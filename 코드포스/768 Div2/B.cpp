#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        int count = 0;
        for (int i = n-1; i > 0;) {
            if (arr[i-1] != arr[i]) {
                for (int j = std::max(2*i-n, 0); j < i; ++j) {
                    arr[j] = arr[j+n-i];
                }
                ++count;
                i = std::max(2*i-n, 0);
            } else {
                --i;
            }
        }

        printf("%d\n", count);
    }

    return 0;
}