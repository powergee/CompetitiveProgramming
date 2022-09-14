#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

typedef long long Long;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());

    int n, m;
    std::cin >> n >> m;
    std::vector<int> courier(n);
    std::vector<std::vector<int>> index(n+1);
    for (int i = 0; i < n; ++i) {
        std::cin >> courier[i];
        index[courier[i]].push_back(i);
    }

    while (m--) {
        int l, r;
        std::cin >> l >> r;
        
        int answer = 0;
        std::uniform_int_distribution<int> dis(l-1, r-1);
        for (int k = 0; k < 20; ++k) {
            int v = courier[dis(gen)];
            int count = std::upper_bound(index[v].begin(), index[v].end(), r-1) - std::lower_bound(index[v].begin(), index[v].end(), l-1);
            if (2*count > r-l+1) {
                answer = v;
                break;
            }
        }
        std::cout << answer << "\n";
    }

    return 0;
}