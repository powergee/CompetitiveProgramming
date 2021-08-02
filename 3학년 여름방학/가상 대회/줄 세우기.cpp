#include <iostream>
#include <algorithm>

int n;
int arr[1000000];
int pos[1000001];
int dp[1000001];

int getCompSize(int startNum) {
    if (dp[startNum]) {
        return dp[startNum];
    } else if (startNum == n || pos[startNum+1] < pos[startNum]) {
        return dp[startNum] = 1;
    } else {
        return dp[startNum] = 1 + getCompSize(startNum+1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        pos[arr[i]] = i;
    }

    int answer = __INT32_MAX__;
    for (int v = 1; v <= n; ++v) {
        answer = std::min(answer, n-getCompSize(v));
    }

    printf("%d", answer);

    return 0;
}