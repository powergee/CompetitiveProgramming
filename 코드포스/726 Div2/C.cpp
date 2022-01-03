#include <iostream>
#include <algorithm>

int arr[200000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        std::sort(arr, arr+n);

        if (n == 2) {
            for (int i = 0; i < n; ++i) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        } else {
            int heightDiff = __INT32_MAX__;
            for (int i = 0; i < n-1; ++i) {
                heightDiff = std::min(heightDiff, arr[i+1]-arr[i]);
            }

            for (int i = 0; i < n-1; ++i) {
                if (heightDiff == arr[i+1]-arr[i]) {
                    for (int j = i+1; j < n; ++j) {
                        printf("%d ", arr[j]);
                    }
                    for (int j = 0; j <= i; ++j) {
                        printf("%d ", arr[j]);
                    }
                    printf("\n");
                    break;
                }
            }
        }
    }

    return 0;
}