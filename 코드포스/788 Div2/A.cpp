#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        int pos = 0, neg = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            pos += (arr[i] > 0 ? 1 : 0);
            neg += (arr[i] < 0 ? 1 : 0);
        }

        bool yes = true;
        if (pos == 0 || neg == 0) {
            for (int i = 0; i+1 < n; ++i) {
                if (arr[i] > arr[i+1]) {
                    yes = false;
                }
            }
        } else {
            for (int i = 0; i+1 < neg; ++i) {
                if (-std::abs(arr[i]) > -std::abs(arr[i+1])) {
                    yes = false;
                }
            }
            for (int i = n-pos; i+1 < n; ++i) {
                if (std::abs(arr[i]) > std::abs(arr[i+1])) {
                    yes = false;
                }
            }
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}