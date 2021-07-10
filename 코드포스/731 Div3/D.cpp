#include <iostream>

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

        printf("0 ");
        for (int i = 1; i < n; ++i) {
            int before = arr[i];
            arr[i] = arr[i-1] | arr[i];
            printf("%d ", arr[i] ^ before);
        }
        printf("\n");
    }

    return 0;
}