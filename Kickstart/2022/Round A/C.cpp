#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

bool isPalindrome(int mask, int length) {
    for (int i = 0; i < 5; ++i) {
        bool left = (mask&(1<<(length-1-i))) > 0;
        bool right = (mask&(1<<i)) > 0;
        if (left != right) {
            return false;
        }
    }
    return true;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        int n;
        std::string input;
        std::cin >> n >> input;

        std::vector<std::vector<int>> dp(n, std::vector<int>(32, -1));
        std::function<bool(int, int)> isPalindromeFree = [&](int last, int mask) -> bool {
            if (last < 4) {
                return true;
            }

            int& result = dp[last][mask];
            if (result != -1) {
                return result;
            }

            bool matched = true;
            for (int i = 0; i < 5; ++i) {
                if (input[last-i] != '?') {
                    bool sBit = input[last-i] != '0';
                    bool mBit = (mask & (1<<i)) > 0;
                    if (sBit != mBit) {
                        matched = false;
                    }
                }
            }
            if (!matched || isPalindrome(mask, 5)) {
                return result = false;
            } else if (!isPalindrome(mask, 6) && isPalindromeFree(last-1, mask>>1)) {
                return result = true;
            } else if (!isPalindrome((1<<5)|mask, 6) && isPalindromeFree(last-1, (1<<4)|(mask>>1))) {
                return result = true;
            }
            return result = false;
        };

        bool possible = false;
        for (int mask = 0; mask < 32; ++mask) {
            if (isPalindromeFree(n-1, mask)) {
                possible = true;
            }
        }

        std::cout << "Case #" << t << ": " << (possible ? "POSSIBLE\n" : "IMPOSSIBLE\n");
    }

    return 0;
}