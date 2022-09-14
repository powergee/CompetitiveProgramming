#include <iostream>
#include <algorithm>

int arr[300000];
int sum[300000];

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    std::sort(arr, arr+n);
    sum[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + arr[i];
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", sum[r-1] - sum[l-1] + arr[l-1]);
    } 

    return 0;
}