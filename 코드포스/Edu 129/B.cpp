#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>

typedef long long Long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<Long> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int m;
    std::cin >> m;
    std::vector<Long> shuffle(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> shuffle[i];
    }

    Long sum = std::accumulate(shuffle.begin(), shuffle.end(), 0LL);
    std::cout << arr[sum % n] << "\n";
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }
    return 0;
}