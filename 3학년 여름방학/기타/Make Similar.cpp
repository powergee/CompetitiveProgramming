#include <iostream>
#include <algorithm>

int arr[100000];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int min = *std::min_element(arr, arr+n);
    int max = *std::max_element(arr, arr+n);

    if (min == max || (min < 0 && 0 < max)) {
        printf("0");
    } else if (min >= 0) {
        printf("%d", std::min(max-min, min));
    } else {
        printf("%d", std::min(max-min, std::abs(max)));
    }

    return 0;
}