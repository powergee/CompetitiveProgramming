#include <iostream>

int main() {
    int n, m;
    int arr[10000];
    int sum[10000];
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }

    sum[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + arr[i];
    }

    int answer = 0;
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (sum[j] - sum[i] + arr[i] < m && j+1 < n) {
            ++j;
        }
        if (sum[j] - sum[i] + arr[i] == m) {
            ++answer;
        }
    }

    printf("%d", answer);

    return 0;
}