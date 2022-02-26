#include <iostream>

int main() {
    int arr[10];
    for (int i = 0; i < 10; ++i) {
        scanf("%d", &arr[i]);
    }
    printf("%d", arr[arr[arr[0]]]);

    return 0;
}