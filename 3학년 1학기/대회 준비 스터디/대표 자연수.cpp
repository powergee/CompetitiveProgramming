#include <iostream>
#include <algorithm>

int n;
int arr[20001];
int sum[20001];

int getDiffSum(int rep) {
    auto found = std::lower_bound(arr+1, arr+n+1, rep);
    int index = found - arr;

    return (rep*(index-1) - sum[index-1]) + (sum[n]-sum[index-1] - rep*(n-index+1));
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr+1, arr+n+1);

    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i-1] + arr[i];
    }

    int min = *std::min_element(arr+1, arr+n+1);
    int max = *std::max_element(arr+1, arr+n+1);

    int answer = min;
    int diff = getDiffSum(min);
    for (int i = min+1; i <= max; ++i) {
        int currDiff = getDiffSum(i);
        if (currDiff < diff) {
            answer = i;
            diff = currDiff;
        }
    }
    
    printf("%d", answer);
    return 0;
}