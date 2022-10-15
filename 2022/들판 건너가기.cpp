#include <iostream>
#include <vector>

int main() {
    const int BEAUTY_MAX = 100;
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;

    std::vector<int> flowers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> flowers[i];
    }

    std::vector<int> dp(n, 0), prevMaxOf(BEAUTY_MAX+1, -1);
    for (int i = 0; i < n; ++i) {
        for (int prevVal = 1; prevVal <= BEAUTY_MAX; ++prevVal) {
            if (prevMaxOf[prevVal] != -1) {
                int diff = (flowers[i]-prevVal);
                dp[i] = std::max(dp[i], diff*diff + prevMaxOf[prevVal]);
            }
        }
        prevMaxOf[flowers[i]] = std::max(prevMaxOf[flowers[i]], dp[i]);
    }

    std::cout << *std::max_element(dp.begin(), dp.end()) << "\n";

    return 0;
}