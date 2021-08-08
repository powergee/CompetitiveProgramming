#include <iostream>
#include <algorithm>

int n;
std::pair<int, int> arr[200000];

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i].first);
        arr[i].second = i;
    }

    std::sort(arr, arr+n);
    printf("%d", arr[n-2].second+1);

    return 0;
}