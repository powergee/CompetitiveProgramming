#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, h;
        scanf("%d %d", &n, &h);

        int arr[1000];
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }
        std::sort(arr, arr+n);
        int a = arr[n-1], b = arr[n-2];
        int answer = h / (a+b) * 2;
        int remain = h % (a+b);
        if (remain == 0) {
            printf("%d\n", answer);
        } else if (remain <= a) {
            printf("%d\n", answer+1);
        } else {
            printf("%d\n", answer+2);
        }
    }

    return 0;
}