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
    std::sort(arr.begin(), arr.end());
    
    int minSum = INT32_MAX, minIdx = 0, minJdx = 0;

    auto update = [&](int i, int j) {
        if (i < j && std::abs(arr[i]+arr[j]) < minSum) {
            minSum = std::abs(arr[i]+arr[j]);
            minIdx = i;
            minJdx = j;
        }
    };

    for (int i = 0; i < n; ++i) {
        auto found = std::lower_bound(arr.begin()+i+1, arr.end(), -arr[i]);
        if (found == arr.end()) {
            update(i, n-1);
        } else {
            int j = found-arr.begin();
            update(i, j);
            update(i, j-1);
        }
    }

    printf("%d %d", arr[minIdx], arr[minJdx]);

    return 0;
}