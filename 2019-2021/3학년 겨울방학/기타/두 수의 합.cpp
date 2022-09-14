#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

int main() {
    int n, sum;
    scanf("%d", &n);
    std::vector<int> arr(n), count(2000001, 0);
    std::for_each(arr.begin(), arr.end(), [&](int& v){scanf("%d", &v);});
    scanf("%d", &sum);

    int answer = 0;
    for (int i = n-1; i > 0; --i) {
        count[arr[i]]++;
        if (sum-arr[i-1] >= 0) {
            answer += count[sum-arr[i-1]];
        }
    }

    printf("%d", answer);

    return 0;
}