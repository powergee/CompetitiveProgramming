#include <iostream>
#include <algorithm>

int getPrize(int arr[3]) {
    for (int v = 1; v <= 6; ++v) {
        int count = 0;
        for (int i = 0; i < 3; ++i) {
            if (arr[i] == v) {
                ++count;
            }
        }
        if (count == 3) {
            return 10000 + 1000*v;
        } else if (count == 2) {
            return 1000 + 100*v;
        }
    }
    return *std::max_element(arr, arr+3) * 100;
}

int main() {
    int arr[3];
    scanf("%d %d %d", arr, arr+1, arr+2);
    printf("%d", getPrize(arr));

    return 0;
}