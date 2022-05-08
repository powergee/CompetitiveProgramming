#include <iostream>
#include <vector>
#include <numeric>

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    std::vector<int> pos(n+1);
    std::vector<int> arr(n+1);
    std::iota(pos.begin(), pos.end(), 0);
    std::iota(arr.begin(), arr.end(), 0);

    for (int i = 0; i < q; ++i) {
        int ball;
        scanf("%d", &ball);
        int p = pos[ball];
        int np = (p == n ? p-1 : p+1);
        int nball = arr[np];
        std::swap(arr[p], arr[np]);
        std::swap(pos[ball], pos[nball]);
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}