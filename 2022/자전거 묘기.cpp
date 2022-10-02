#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n;
    std::cin >> n;

    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> heights[i];
    }

    std::vector<int> dp(n);
    for (int i = n-1; i >= 0; --i) {
        int dst = i + heights[i] + 1;
        if (dst > n-1) {
            dp[i] = 1;
        } else {
            dp[i] = 1 + dp[dst];
        }
    }

    for (int i = 0; i < n; ++i) {
        std::cout << dp[i] << " ";
    }

    return 0;
}