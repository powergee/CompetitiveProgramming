#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

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

        int sum = std::accumulate(arr.begin(), arr.end(), 0);
        int min = *std::min_element(arr.begin(), arr.end());
        printf("%d\n", sum-min*n);
    }

    return 0;
}