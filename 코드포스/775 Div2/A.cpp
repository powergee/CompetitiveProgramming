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

        int start = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i]) {
                start = i;
            } else {
                break;
            }
        }

        int end = n-1;
        for (int i = n-1; i >= 0; --i) {
            if (arr[i]) {
                end = i;
            } else {
                break;
            }
        }

        if (start < end) {
            printf("%d\n", end-start);
        } else {
            printf("0\n");
        }
    }

    return 0;
}