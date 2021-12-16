#include <cstdio>
#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        int max = arr[n-1];
        int changeCount = 1;
        for (int i = n-1; i >= 0; --i) {
            if (max < arr[i]) {
                max = arr[i];
                changeCount++;
            }
        }

        printf("%d\n", changeCount-1);
    }

    return 0;
}
