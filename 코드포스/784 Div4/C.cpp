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

        bool evenSame = true, oddSame = true;
        for (int i = 2; i < n; i += 2) {
            if (arr[i]%2 != arr[0]%2) {
                evenSame = false;
            }
        }
        for (int i = 3; i < n; i += 2) {
            if (arr[i]%2 != arr[1]%2) {
                oddSame = false;
            }
        }

        if (evenSame && oddSame) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}