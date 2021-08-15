#include <iostream>
#include <algorithm>

typedef long long Long;

int n;
Long arr[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);

        Long sum = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%lld", arr+i);
            sum += arr[i];
        }

        std::sort(arr, arr+n);
        Long left = 0;
        Long right = sum;
        double answer = -__INT64_MAX__;
        for (int i = 0; i < n-1; ++i) {
            left += arr[i];
            right -= arr[i];
            double current = ((double)left / (i+1)) + ((double)right / (n-i-1));
            answer = std::max(answer, current);
        }

        printf("%.10lf\n", answer);
    }

    return 0;
}