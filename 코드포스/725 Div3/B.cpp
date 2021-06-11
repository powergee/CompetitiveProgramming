#include <iostream>
#include <algorithm>

int arr[200000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        std::sort(arr, arr+n, std::greater<int>());
        int totalGap = 0;
        for (int i = 1; i < n; ++i) {
            totalGap += arr[0] - arr[i];
        }

        int spare = 0;
        int answer = -1;
        for (int i = 0; i < n; ++i) {
            int need = totalGap + (arr[i] * i);
            if (need <= spare && (spare - need) % n == 0) {
                answer = i;
                break;
            }

            spare += arr[i];
            if (i+1 < n) {
                totalGap -= (arr[i] - arr[i+1]) * (n-i-1); 
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}