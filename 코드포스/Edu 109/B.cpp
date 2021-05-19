#include <iostream>
#include <algorithm>

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n-1; ++i) {
        if (arr[i] > arr[i+1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int arr[50];

        int firstPos, lastPos;
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
            if (arr[i] == 1) {
                firstPos = i;
            }
            if (arr[i] == n) {
                lastPos = i;
            }
        }

        if (isSorted(arr, n)) {
            printf("0\n");
        } else {
            if (firstPos == 0 || lastPos == n-1) {
                printf("1\n");
            } else if (firstPos == n-1 && lastPos == 0) {
                printf("3\n");
            } else {
                printf("2\n");
            }
        }
    }
}