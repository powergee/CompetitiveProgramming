#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#define GREATER 0
#define LESS 1

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    std::vector<std::vector<int>> dp(n, std::vector<int>(2, -1));
    std::vector<std::vector<std::pair<int, int>>> trans(n, std::vector<std::pair<int, int>>(2, {-1, -1}));
    std::function<int(int, int)> comparer[2] = { std::greater<int>(), std::less<int>() };
    
    std::function<int(int, int)> getMaxLength = [&](int prev, int currCond) -> int {
        int& result = dp[prev][currCond];
        if (result != -1) {
            return result;
        }

        result = 1;
        for (int next = prev+1; next < n; ++next) {
            if (comparer[currCond](arr[prev], arr[next])) {
                int sub = 1+getMaxLength(next, !currCond);
                if (result < sub) {
                    result = sub;
                    trans[prev][currCond] = { next, !currCond };
                }
            }
        }
        return result;
    };

    int maxLen = -1;
    std::pair<int, int> state;
    for (int i = 0; i < n; ++i) {
        if (maxLen < getMaxLength(i, GREATER)) {
            maxLen = getMaxLength(i, GREATER);
            state = { i, GREATER };
        }
        if (maxLen < getMaxLength(i, LESS)) {
            maxLen = getMaxLength(i, LESS);
            state = { i, LESS };
        }
    }

    std::vector<bool> used(n, false);
    while (state.first != -1) {
        used[state.first] = true;
        state = trans[state.first][state.second];
    }

    std::vector<int> answer;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            answer.push_back(i);
        }
    }

    printf("%d\n", int(answer.size()));
    for (int v : answer) {
        printf("%d ", v+1);
    }

    return 0;
}