#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n+1), sum(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
            sum[i] = sum[i-1] + arr[i];
        }

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            int alice = sum[i];
            int l = i+1, r = n;
            while (l < r) {
                int m = (l+r)/2;
                int bob = sum[n]-sum[m-1];
                if (alice == bob) {
                    l = r = m;
                } else if (alice < bob) {
                    l = m+1;
                } else {
                    r = m-1;
                }
            }
            int bob = sum[n]-sum[l-1];
            if (alice == bob) {
                answer = std::max(answer, i+(n-l+1));
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}