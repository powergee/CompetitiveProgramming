#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    Long n, w;
    scanf("%lld %lld", &n, &w);

    std::vector<Long> weight(n), value(n);
    Long valueSum = 0;

    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &weight[i], &value[i]);
        valueSum += value[i];
    }

    std::vector<Long> minWeights(valueSum+1, INT64_MAX);
    minWeights[0] = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = valueSum; j >= 0; --j) {
            if (minWeights[j] != INT64_MAX && j+value[i] <= valueSum) {
                minWeights[j+value[i]] = std::min(minWeights[j+value[i]], minWeights[j]+weight[i]);
            }
        }
    }

    int answer = 0;
    for (int i = 0; i <= valueSum; ++i) {
        if (minWeights[i] <= w) {
            answer = i;
        }
    }

    printf("%d", answer);

    return 0;
}