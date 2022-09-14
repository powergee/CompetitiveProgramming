#include <iostream>
#include <numeric>
#include <algorithm>

int main() {
    int arr[4];
    for (int i = 0; i < 4; ++i) {
        scanf("%d", arr+i);
    }

    if (std::adjacent_find(arr, arr+4, [](int a, int b) { return a >= b; }) == arr+4) {
        printf("Fish Rising\n");
    } else if (std::adjacent_find(arr, arr+4, [](int a, int b) { return a <= b; }) == arr+4) {
        printf("Fish Diving\n");
    } else if (std::equal(arr+1, arr+4, arr)) {
        printf("Fish At Constant Depth\n");
    } else {
        printf("No Fish\n");
    }

    return 0;
}