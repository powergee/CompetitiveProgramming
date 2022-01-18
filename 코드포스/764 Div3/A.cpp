#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        int arr[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }
        printf("%d\n", *std::max_element(arr, arr+n) - *std::min_element(arr, arr+n));
    }

    return 0;
}