#include <iostream>

int arr[1000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        printf("%d\n", n*3);
        for (int i = 0; i < n; i += 2) {
            printf("1 %d %d\n", i+1, i+2);
            printf("2 %d %d\n", i+1, i+2);
            printf("1 %d %d\n", i+1, i+2);

            printf("1 %d %d\n", i+1, i+2);
            printf("2 %d %d\n", i+1, i+2);
            printf("1 %d %d\n", i+1, i+2);
        }
    }

    return 0;
}