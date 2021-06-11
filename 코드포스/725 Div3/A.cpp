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

        auto max = std::max_element(arr, arr+n);
        auto min = std::min_element(arr, arr+n);
        int maxIdx = max - arr;
        int minIdx = min - arr;

        if (maxIdx < minIdx) {
            std::swap(maxIdx, minIdx);
        }

        int answer[] = {
            minIdx+1 + n-maxIdx,
            maxIdx+1,
            n-minIdx
        };

        printf("%d\n", *std::min_element(answer, answer+3));
    }

    return 0;
}