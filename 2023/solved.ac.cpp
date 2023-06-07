#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << 0 << "\n";
        return 0;
    }

    std::vector<int> tier(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> tier[i];
    }
    std::sort(tier.begin(), tier.end());
    int remove = std::round(n * 0.15);
    int total = 0;
    for (int i = 0; i < n - remove * 2; ++i) {
        total += tier[remove + i];
    }
    std::cout << int(std::round(total * 1.0 / (n - remove * 2))) << "\n";
    return 0;
}