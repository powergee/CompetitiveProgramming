#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> arr(n);
    std::for_each(arr.begin(), arr.end(), [](Long& v) { scanf("%lld", &v); });
    
    std::vector<Long> base(n+2, 0LL);
    for (int i = 0; i < n-1; ++i) {
        Long diff = arr[i+1] - arr[i];
        base[i+3] = base[i] + diff;
    }

    Long mins[3] = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = i; j < n+2; j += 3) {
            mins[i] = std::min(mins[i], base[j]);
        }
    }

    Long minSum = -mins[0]-mins[1]-mins[2];
    if (minSum <= arr[0]) {
        printf("Yes\n");
        Long start[3] = { -mins[0]+(arr[0]-minSum), -mins[1], -mins[2] };
        for (int i = 0; i < 3; ++i) {
            for (int j = i; j < n+2; j += 3) {
                base[j] += start[i];
            }
        }
        for (int i = 0; i < n+2; ++i) {
            printf("%lld ", base[i]);
        }
    } else {
        printf("No\n");
    }

    return 0;
}