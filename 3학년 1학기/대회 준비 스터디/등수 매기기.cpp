#include <iostream>
#include <algorithm>

int arr[500000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+n);

    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        answer += std::abs(arr[i] - (i+1));
    }
    printf("%lld", answer);

    return 0;
}