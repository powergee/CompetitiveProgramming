#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        bool zeroExist = false, oneExist = false;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            arr[i] = val;
            if (val == 0) {
                zeroExist = true;
            } else if (val == 1) {
                oneExist = true;
            }
        }
        
        bool possible = true;
        if (oneExist && zeroExist) {
            possible = false;
        } else if (oneExist) {
            std::sort(arr.begin(), arr.end(), std::greater<int>());
            // Set them to 1.
            for (int i = 0; i+1 < n; ++i) {
                if (arr[i]-1 == arr[i+1]) {
                    possible = false;
                    goto PRINT;
                }
            }
            for (int i = 0; i < n; ++i) {
                if (arr[i] == 2) {
                    possible = false;
                    goto PRINT;
                }
            }
            possible = true;
        } else {
            possible = true;
        }
        PRINT:
        printf(possible ? "YES\n" : "NO\n");
    }

    return 0;
}