#include <iostream>
#include <algorithm>

int arr[1000];
int dp[1000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    dp[0] = arr[0];
    int answer = dp[0];
    for (int i = 1; i < n; ++i) {
        dp[i] = arr[i];
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[i]) {
                dp[i] = std::max(dp[i], dp[j] + arr[i]);
            }
        }

        answer = std::max(answer, dp[i]);
    }

    printf("%d", answer);

    return 0;
}