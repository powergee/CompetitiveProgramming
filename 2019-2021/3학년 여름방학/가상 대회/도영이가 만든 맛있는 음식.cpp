#include <iostream>

int main() {
    int n;
    scanf("%d", &n);

    std::pair<int, int> ingredients[n];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &ingredients[i].first, &ingredients[i].second);
    }

    int answer = __INT32_MAX__;
    for (int mask = 1; mask < (1<<n); ++mask) {
        int sMult = 1;
        int bSum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1<<i)) {
                sMult *= ingredients[i].first;
                bSum += ingredients[i].second;
            }
        }
        int diff = std::abs(sMult-bSum);
        answer = std::min(diff, answer);
    }

    printf("%d", answer);

    return 0;
}