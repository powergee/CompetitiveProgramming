#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        int arr[n];

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        std::vector<std::tuple<int, int, int>> answer;
        for (int end = n; end > 0; --end) {
            auto max = std::max_element(arr, arr+end);
            int maxNum = max - arr + 1;
            if (maxNum != end) {
                answer.emplace_back(maxNum, end, 1);
                for (int i = maxNum-1; i < end-1; ++i) {
                    arr[i] = arr[i+1];
                }
                arr[end-1] = *max;
            }
        }

        printf("%d\n", (int)answer.size());
        for (auto[l, r, d] : answer) {
            printf("%d %d %d\n", l, r, d);
        }
    }

    return 0;
}