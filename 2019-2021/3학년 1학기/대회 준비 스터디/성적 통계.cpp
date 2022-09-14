#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Class %d\n", t);

        int n;
        scanf("%d", &n);

        int arr[50];
        int min = 101, max = -1;
        for (int i = 0; i < n; ++i) {
            int s;
            scanf("%d", &s);
            min = std::min(s, min);
            max = std::max(s, max);
            arr[i] = s;
        }

        std::sort(arr, arr+n);
        int gap = -1;
        for (int i = 0; i < n-1; ++i) {
            gap = std::max(gap, std::abs(arr[i] - arr[i+1]));
        }

        printf("Max %d, Min %d, Largest gap %d\n", max, min, gap);
    }

    return 0;
}