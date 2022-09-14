#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    int answer = *std::max_element(arr.begin(), arr.end());
    for (int i = 1; i < n-1; ++i) {
        answer = std::max(answer, arr[i] + std::min(arr[i-1], arr[i+1]));
    }
    printf("%d", answer);

    return 0;
}