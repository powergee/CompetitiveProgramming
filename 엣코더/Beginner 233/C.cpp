#include <iostream>
#include <vector>
#include <algorithm>

typedef long long Long;

int main() {
    Long n, x;
    scanf("%lld %lld", &n, &x);
    std::vector<std::vector<Long>> bags(n);

    for (int i = 0; i < n; ++i) {
        int l;
        scanf("%d", &l);
        bags[i].resize(l);
        for (int j = 0; j < l; ++j) {
            scanf("%lld", &bags[i][j]);
        }
    }

    std::function<Long(int, Long)> countCases;
    countCases = [&](int bIdx, Long goal) -> Long {
        if (bIdx == n) {
            return goal == 1 ? 1 : 0;
        }
        Long result = 0;
        for (int ball : bags[bIdx]) {
            if (goal % ball == 0 && goal >= ball) {
                result += countCases(bIdx+1, goal/ball);
            }
        }
        return result;
    };
    printf("%lld", countCases(0, x));

    return 0;
}