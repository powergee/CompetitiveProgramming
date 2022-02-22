#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int answer = 0;
    int window = std::accumulate(arr.begin(), arr.begin()+k, 0);
    for (int i = 0; i < n; ++i) {
        answer = std::max(answer, window);
        window += arr[(i+k) % n] - arr[i];
    }
    
    printf("%d", answer);

    return 0;
}