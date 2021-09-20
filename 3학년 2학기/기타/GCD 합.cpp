#include <iostream>
#include <numeric>
#include <set>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                sum += std::gcd(arr[i], arr[j]);
            }
        }
        printf("%lld\n", sum);
    }

    return 0;
}