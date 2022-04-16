#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n+1), sum(n+1);
        std::vector<int> count(n+1, 0);
        std::vector<int> exist(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
            count[arr[i]]++;
        }

        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i-1] + arr[i];
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i+1; j <= n; ++j) {
                int currSum = sum[j]-sum[i-1];
                if (currSum <= n) {
                    exist[currSum] = 1;
                }
            }
        }

        int answer = 0;
        for (int i = 1; i <= n; ++i) {
            answer += count[i] * exist[i];
        }
        printf("%d\n", answer);
    }

    return 0;
}