#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);
    std::vector<int> weight(n);
    std::for_each(weight.begin(), weight.end(), [](int& val) { scanf("%d", &val); });
    
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(55001, -1));

    std::function<bool(int, int)> isPossible = [&](int wCount, int toMake) -> bool {
        int& result = dp[wCount][toMake];
        if (result != -1) {
            return result;
        }

        if (wCount == 0) {
            return result = toMake == 0 ? true : false;
        } else {
            return result = isPossible(wCount-1, toMake) || isPossible(wCount-1, std::abs(toMake-weight[wCount-1])) || isPossible(wCount-1, toMake+weight[wCount-1]);
        }
    };

    int q;
    scanf("%d", &q);
    while (q--) {
        int toMake;
        scanf("%d", &toMake);
        printf(isPossible(n, toMake) ? "Y " : "N ");
    }

    return 0;
}