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

    dp[0] = 1;
    int answer = 1;
    for (int i = 1; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (arr[i] < arr[j]) {
                dp[i] = std::max(dp[i], dp[j] + 1);
            }
        }

        answer = std::max(answer, dp[i]);
    }

    printf("%d", answer);

    return 0;
}