#include <iostream>
#include <algorithm>

int arr[10000];

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


        int answer = std::max(std::abs(arr[0]-arr[1]), std::abs(arr[n-2]-arr[n-1]));
        for (int i = 0; i < n-2; ++i) {
            answer = std::max(answer, std::abs(arr[i]-arr[i+2]));
        }
        printf("%d\n", answer);
    }

    return 0;
}