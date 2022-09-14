#include <iostream>
#include <algorithm>

int main() {
    int l, n;
    int arr[50];
    scanf("%d", &l);
    for (int i = 0; i < l; ++i) {
        scanf("%d", arr+i);
    }
    scanf("%d", &n);

    std::sort(arr, arr+l);
    auto found = std::lower_bound(arr, arr+l, n);

    if (found == arr+l || *found == n) {
        printf("0");
    } else {
        int lower = arr == found ? 1 : (*(found-1)+1);
        int upper = *found-1;
        int answer = 0;
        for (int i = lower; i < upper; ++i) {
            for (int j = i+1; j <= upper; ++j) {
                if (i <= n && n <= j) {
                    ++answer;
                }
            }
        }

        printf("%d", answer);
    }

    return 0;
}