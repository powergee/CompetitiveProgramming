#include <iostream>
#include <vector>
#include <numeric>

int main() {
    int x, n;
    scanf("%d %d", &x, &n);
    std::vector<int> arr(n+1);
    arr[1] = x;
    for (int i = 2; i <= n; ++i) {
        if (i % 5 == 0) {
            arr[i] = arr[i-1] - 2;
        } else {
            arr[i] = arr[i-1] + 1;
        }
    }
    int sum = std::accumulate(arr.begin()+1, arr.end(), 0);
    printf("%d", sum);

    return 0;
}