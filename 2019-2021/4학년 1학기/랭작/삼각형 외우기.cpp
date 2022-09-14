#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int arr[3];
    for (int i = 0; i < 3; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+3);

    if (std::accumulate(arr, arr+3, 0) != 180) {
        printf("Error");
    } else if (arr[0] == arr[1] && arr[1] == arr[2]) {
        printf("Equilateral");
    } else if (arr[0] == arr[1] || arr[1] == arr[2]) {
        printf("Isosceles");
    } else {
        printf("Scalene");
    }

    return 0;
}