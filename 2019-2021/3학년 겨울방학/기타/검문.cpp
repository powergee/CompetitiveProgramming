#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n);
    std::for_each(arr.begin(), arr.end(), [](int& v){ scanf("%d", &v); });
    std::sort(arr.begin(), arr.end());
    std::adjacent_difference(arr.begin(), arr.end(), arr.begin());
    int gcd = std::accumulate(arr.begin()+1, arr.end(), arr[1], std::gcd<int, int>);

    std::vector<int> answer { gcd };
    for (long long v = 2; v*v <= gcd; ++v) {
        if (gcd % v == 0) {
            if (gcd/v == v) {
                answer.push_back(int(v));
            } else {
                answer.push_back(int(v));
                answer.push_back(int(gcd/v));
            }
        }
    }
    std::sort(answer.begin(), answer.end());
    std::for_each(answer.begin(), answer.end(), [](int ans){ printf("%d ", ans); });
    return 0;
}