#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

using Long = long long;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        std::vector<Long> arr(n+1);
        std::vector<std::vector<Long>> sum(n+1, std::vector<Long>(n+1, 0));
        for (int i = 1; i <= n; ++i) {
            Long v;
            scanf("%lld", &v);
            arr[i] = v;
            sum[i][v]++;
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
            }
        }

        auto countValues = [&](int i, int j, int lower, int upper) -> Long {
            if (i > j || lower > upper) {
                return 0;
            }
            return sum[j][upper] - sum[i-1][upper] - sum[j][lower-1] + sum[i-1][lower-1];
        };

        Long answer = 0;
        for (int i = 1; i+3 <= n; ++i) {
            Long count = 0;
            for (int j = i+2; j+1 <= n; ++j) {
                Long added = arr[j-1];
                Long removed = arr[j];
                count -= countValues(i+1, j-2, removed+1, n);
                count += countValues(j+1, n, 1, added-1);
                if (arr[i] < arr[j]) {
                    answer += count;
                }
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}