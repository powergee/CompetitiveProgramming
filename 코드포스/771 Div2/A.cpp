#include <iostream>
#include <vector>
#include <algorithm>

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

        for (int i = 0; i < n; ++i) {
            if (arr[i] != i+1) {
                auto min = std::min_element(arr.begin()+i, arr.end());
                std::reverse(arr.begin()+i, min+1);
                break;
            }
        }

        for (int i = 0; i < n; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}