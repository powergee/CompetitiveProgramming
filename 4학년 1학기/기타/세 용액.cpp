#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
    }
    std::sort(arr.begin(), arr.end());

    Long a = INT32_MAX, b = INT32_MAX, c = INT32_MAX;
    for (int i = 0; i < n-2; ++i) {
        int left = i+1, right = n-1;
        while (left < right) {
            Long currSum = arr[i]+arr[left]+arr[right];
            if (std::abs(currSum) < std::abs(a+b+c)) {
                a = arr[i];
                b = arr[left];
                c = arr[right];
            }
            if (currSum < 0) {
                ++left;
            } else if (currSum > 0) {
                --right;
            } else {
                break;
            }
        }
    }

    printf("%lld %lld %lld", a, b, c);

    return 0;
}