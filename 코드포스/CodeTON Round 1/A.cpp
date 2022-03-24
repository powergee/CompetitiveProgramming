#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<std::pair<int, int>> arr(n);
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            arr[i] = { val, i };
        }
        std::sort(arr.begin(), arr.end());
        printf("%d %d\n", arr.front().second+1, arr.back().second+1);
    }

    return 0;
}