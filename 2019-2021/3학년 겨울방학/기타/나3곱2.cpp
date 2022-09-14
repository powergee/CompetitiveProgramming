#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int countPower(Long val, int base) {
    int result = 0;
    while (val % base == 0) {
        ++result;
        val /= base;
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> arr(n), index(n);
    std::vector<int> two(n, 0), three(n, 0);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &arr[i]);
        index[i] = i;
        two[i] = countPower(arr[i], 2);
        three[i] = countPower(arr[i], 3);
    }

    int minTwo = *std::min_element(two.begin(), two.end());
    int maxThree = *std::max_element(three.begin(), three.end());

    std::sort(index.begin(), index.end(), [&](int idx1, int idx2) -> bool {
        int count1 = (two[idx1]-minTwo) + (maxThree-three[idx1]);
        int count2 = (two[idx2]-minTwo) + (maxThree-three[idx2]);
        return count1 < count2;
    });

    for (int idx : index) {
        printf("%lld ", arr[idx]);
    }

    return 0;
}