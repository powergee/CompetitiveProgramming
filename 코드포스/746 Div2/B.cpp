#include <iostream>
#include <algorithm>

int arr[100000];
int sorted[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, x;
        scanf("%d %d", &n, &x);
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
            sorted[i] = arr[i];
        }
        std::sort(sorted, sorted+n);

        auto isValid = [&](int i) -> bool {
            return (0 <= i-x || i+x < n);
        };

        bool possible = true;
        for (int i = 0; i < n; ++i) {
            if (!isValid(i) && arr[i] != sorted[i]) {
                possible = false;
                break;
            }
        }

        if (possible) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}