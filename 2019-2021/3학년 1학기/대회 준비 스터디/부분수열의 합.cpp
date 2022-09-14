#include <iostream>

bool canMake[2000001];

int main() {
    int n;
    int arr[20];
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    for (int sel = 1; sel < (1<<n); ++sel) {
        int sum = 0;
        for (int i = 0; (1<<i) <= sel; ++i) {
            if (sel & (1<<i)) {
                sum += arr[i];
            }
        }
        canMake[sum] = true;
    }

    for (int i = 1; i < 2000001; ++i) {
        if (!canMake[i]) {
            printf("%d", i);
            break;
        }
    }

    return 0;
}