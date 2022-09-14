#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);

        int n;
        int arr[100];
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        int sum = 0;
        for (int i = 0; i < n-1; ++i) {
            auto min = std::min_element(arr+i, arr+n);
            sum += min - (arr+i) + 1;
            std::reverse(arr+i, min+1);
        }

        printf("%d\n", sum);
    }
}