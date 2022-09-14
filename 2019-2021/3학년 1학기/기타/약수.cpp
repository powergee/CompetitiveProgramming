#include <iostream>
#include <algorithm>

int main() {
    int n, arr[50];
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+n);
    printf("%lld", (long long)arr[0] * arr[n-1]);
}