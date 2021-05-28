#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int arr[2*n];

        for (int i = 0; i < 2*n; ++i) {
            scanf("%d", arr+i);
        }

        std::sort(arr, arr+2*n);
        int j = 0;
        int answer[2*n];
        for (int i = 0; i < 2*n; i += 2) {
            answer[i] = arr[j++];
        }
        for (int i = 2*n-1; i >= 0; i -= 2) {
            answer[i] = arr[j++];
        }

        for (int i = 0; i < 2*n; ++i) {
            printf("%d ", answer[i]);
        }
        printf("\n");
    }

    return 0;
}