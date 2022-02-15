#include <iostream>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);

        std::vector<int> arr(n), count(n+1, 0);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
            count[arr[i]]++;
        }

        auto getInterval = [&](int width) -> std::pair<int, int> {
            // init window
            int in = 0, out = n;
            for (int i = 1; i <= width-1; ++i) {
                in += count[i];
                out -= count[i];
            }

            for (int i = width; i <= n; ++i) {
                in += count[i];
                out -= count[i];
                if (in >= out+k) {
                    return {i-width+1, i};
                }
                in -= count[i-width+1];
                out += count[i-width+1];
            }
            return {-1, -1};
        };

        int left = 1, right = n;
        while (left+1 < right) {
            int mid = (left+right)/2;
            auto interval = getInterval(mid);
            if (interval.first != -1) {
                right = mid;
            } else {
                left = mid;
            }
        }

        int width = (getInterval(left).first == -1 ? right : left);
        auto interval = getInterval(width);
        printf("%d %d\n", interval.first, interval.second);

        int l = 0, in = 0;
        for (int r = 0; r < n && k > 1; ++r) {
            if (interval.first <= arr[r] && arr[r] <= interval.second) {
                ++in;
            }
            int out = r-l+1 - in;
            if (in > out) {
                printf("%d %d\n", l+1, r+1);
                l = r+1;
                in = 0;
                --k;
            }
        }

        if (k > 0 && l < n) {
            printf("%d %d\n", l+1, n);
        }
    }

    return 0;
}