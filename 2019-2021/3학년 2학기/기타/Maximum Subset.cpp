#include <iostream>
#include <algorithm>

int n, k;
int arr[100000];

bool ableToSatisfy(int minDist) {
    auto ptr = arr;
    int count = 1;
    while (count < k) {
        ptr = std::lower_bound(arr, arr+n, *ptr+minDist);
        ++count;
        if (ptr == arr+n) {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+n);

    int left = 0, right = arr[n-1]-arr[0]+1;
    while (left+1 < right) {
        int mid = (left+right)/2;
        if (ableToSatisfy(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    printf("%d", left);

    return 0;
}