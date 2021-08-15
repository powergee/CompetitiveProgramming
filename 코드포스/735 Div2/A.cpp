#include <iostream>
#include <algorithm>

long long arr[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%lld", arr+i);
        }

        long long answer = 0;
        for (int i = 0; i < n-1; ++i) {
            long long curr = arr[i] * arr[i+1];
            answer = std::max(answer, curr);
        }

        printf("%lld\n", answer);
    }

    return 0;
}