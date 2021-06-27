#include <iostream>
#include <algorithm>

int arr[250000];

int main() {
    int n, x;
    scanf("%d %d", &n, &x);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    int sum = 0;
    for (int i = 0; i < x; ++i) {
        sum += arr[i];
    }

    int maxSum = sum;
    int maxCount = 1;
    for (int i = x; i < n; ++i) {
        sum += arr[i];
        sum -= arr[i-x];
        if (maxSum < sum) {
            maxSum = sum;
            maxCount = 1;
        } else if (maxSum == sum) {
            maxCount++;
        }
    }

    if (maxSum == 0) {
        printf("SAD");
    } else {
        printf("%d\n%d", maxSum, maxCount);
    }

    return 0;
}