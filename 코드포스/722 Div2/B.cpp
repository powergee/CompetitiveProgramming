#include <iostream>
#include <algorithm>

int arr[100000];
int diff[100000];
int minDiff[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }
        std::sort(arr, arr+n);

        for (int i = 0; i < n-1; ++i) {
            diff[i] = arr[i+1] - arr[i];
        }

        minDiff[0] = diff[0];
        for (int i = 1; i < n-1; ++i) {
            minDiff[i] = std::min(minDiff[i-1], diff[i]);
        }

        int answer = 1;
        for (int i = 1; i < n; ++i) {
            if (minDiff[i-1] >= arr[i]) {
                answer = i+1;
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}