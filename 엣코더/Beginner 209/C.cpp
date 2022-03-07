#include <iostream>
#include <algorithm>

int arr[200000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+n);

    long long result = 1;
    for (int i = 0; i < n; ++i) {
        result *= std::max(arr[i]-i, 0);
        result %= 1000000007;
    }

    printf("%lld", result);
}