#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<char> colors(n);
    std::vector<int> count(n);
    std::vector<std::vector<Long>> dp(n);

    for (int i = 0; i < n; ++i) {
        char str[2];
        scanf("%s %d", str, &count[i]);
        colors[i] = str[0];
    }

    auto addVectors = [](std::vector<Long>& v1, std::vector<Long>& v2) -> std::vector<Long> {
        std::vector<Long>* shorter = (v1.size() < v2.size() ? &v1 : &v2);
        std::vector<Long>* longer = (v1.size() < v2.size() ? &v2 : &v1);

        std::vector<Long> result = *longer;
        for (int i = 0; i < shorter->size(); ++i) {
            result[i] += shorter->at(i);
        }
        return result;
    };

    dp[0] = std::vector<Long> { 1 };
    for (int i = 1; i < n; ++i) {
        dp[i] = addVectors(dp[i-1], dp[i-1]);
        dp[i].resize(i+1, 1);
    }
    std::vector<Long> moved = dp[n-1];

    auto isSatisfied = [&](int index) -> bool {
        if (count[index] == 1) {
            return true;
        }
        
        switch (colors[index])
        {
        case 'R':
            return moved[index] % 2 == 1;
        case 'B':
            return moved[index] % 2 == 0;
        default:
            return true;
        }
    };

    for (int i = n-1; i > 0; --i) {
        if (!isSatisfied(i)) {
            moved[i]++;
            moved = addVectors(moved, dp[i-1]);
        }
    }

    Long answer = 0;
    for (int i = 1; i < n; ++i) {
        answer += moved[i] * count[i];
    }

    if (isSatisfied(0)) {
        answer += moved[0] * count[0];
    } else {
        answer += (moved[0]+1) * count[0] - 1;
    }

    printf("%lld", answer);

    return 0;
}