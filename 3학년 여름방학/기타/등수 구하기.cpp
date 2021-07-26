#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, score, p;
    scanf("%d %d %d", &n, &score, &p);

    std::vector<int> scores;

    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        scores.push_back(val);
    }

    auto upper = std::upper_bound(scores.begin(), scores.end(), score, std::greater<int>());
    auto lower = std::lower_bound(scores.begin(), scores.end(), score, std::greater<int>());
    int worst = upper - scores.begin() + 1;
    int place = lower - scores.begin() + 1;

    if (p < worst) {
        printf("-1");
    } else {
        printf("%d", place);
    }

    return 0;
}