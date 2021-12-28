#include <iostream>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int arr[3];
        for (int i = 0; i < 3; ++i) {
            scanf("%d", arr+i);
        }

        printf("%d ", std::max(std::max(arr[1], arr[2])+1 - arr[0], 0));
        printf("%d ", std::max(std::max(arr[0], arr[2])+1 - arr[1], 0));
        printf("%d\n", std::max(std::max(arr[0], arr[1])+1 - arr[2], 0));
    }

    return 0;
}