#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> arr(5);
    for (int i = 0; i < 5; ++i) {
        int v;
        scanf("%d", &v);
        arr[i] = v;
    }

    int answer = INT32_MAX;
    for (int i = 0; i < 5; ++i) {
        for (int j = i+1; j < 5; ++j) {
            for (int k = j+1; k < 5; ++k) {
                int lcm = arr[i]*arr[j] / std::gcd(arr[i], arr[j]);
                lcm = lcm*arr[k] / std::gcd(lcm, arr[k]);
                answer = std::min(answer, lcm);
            }
        }
    }

    printf("%d", answer);
    
    return 0;
}