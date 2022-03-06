#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <numeric>

bool isIntegral(std::vector<int>& arr, int c) {
    std::set<int> arrSet(arr.begin(), arr.end());
    std::vector<int> exist(c+1, 0);
    for (int v : arrSet) {
        exist[v] = 1;
    }
    std::vector<int> sum(c+1);
    std::partial_sum(exist.begin(), exist.end(), sum.begin());

    for (int y : arrSet) {
        for (int floor = 1; y*floor <= c; ++floor) {
            int left = y*floor;
            int right = std::min(y*(floor+1)-1, c);
            if (sum[right]-sum[left-1] && arrSet.count(floor) == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, c;
        scanf("%d %d", &n, &c);

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }

        if (isIntegral(arr, c)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}