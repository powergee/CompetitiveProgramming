#include <iostream>
#include <algorithm>

int arr[1000000];
int lis[1000000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::fill(lis, lis+n, __INT32_MAX__);

    int length = 0;
    for (int i = 0; i < n; ++i) {
        auto found = std::lower_bound(lis, lis+n, arr[i]);
        *found = arr[i];
        length = std::max(length, (int)(found - lis)+1);
    }

    printf("%d", length);

    return 0;
}