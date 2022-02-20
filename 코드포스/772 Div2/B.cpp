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

        int changed = 0;
        for (int i = 2; i < n; ++i) {
            if (arr[i-2] < arr[i-1] && arr[i-1] > arr[i]) {
                if (i == n-1) {
                    arr[i] = arr[i-1];
                } else {
                    arr[i] = std::max(arr[i-1], arr[i+1]);
                }
                ++changed;
            }
        }

        printf("%d\n", changed);
        for (int i = 0; i < n; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}