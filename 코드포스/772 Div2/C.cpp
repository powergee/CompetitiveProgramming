#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

typedef long long Long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        std::vector<std::tuple<int, int, int>> answer;
        std::tuple<Long, int, int> minSub = std::make_tuple(arr[n-2]-arr[n-1], n-2, n-1);
        for (int i = n-3; i >= 0; --i) {
            auto [minSubVal, left, right] = minSub;
            if (arr[i] > arr[i+1]) {
                arr[i] = minSubVal;
                answer.emplace_back(i, left, right);
            }
            if (arr[i] - arr[n-1] < minSubVal) {
                minSub = std::make_tuple(arr[i] - arr[n-1], i, n-1);
            }
        }

        if (std::is_sorted(arr.begin(), arr.end())) {
            printf("%d\n", (int)answer.size());
            for (auto [i, j, k] : answer) {
                printf("%d %d %d\n", i+1, j+1, k+1);
            }
        } else {
            printf("-1\n");
        }
    }

    return 0;
}