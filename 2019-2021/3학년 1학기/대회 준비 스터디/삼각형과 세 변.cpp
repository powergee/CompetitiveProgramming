#include <iostream>
#include <algorithm>

int main() {
    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c), a != 0 && b != 0 && c != 0) {
        int arr[] = {a, b, c};
        std::sort(arr, arr+3);
        if (arr[2] >= arr[0]+arr[1]) {
            printf("Invalid\n");
        } else if (a == b && b == c) {
            printf("Equilateral\n");
        } else if (a == b || b == c || a == c) {
            printf("Isosceles\n");
        } else {
            printf("Scalene\n");
        }
    }

    return 0;
}