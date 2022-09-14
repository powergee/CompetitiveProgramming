#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef long long Long;

int main() {
    Long n, w;
    scanf("%lld %lld", &n, &w);

    std::vector<Long> weight(n), value(n);
    std::for_each(weight.begin(), weight.end(), [](Long& v) {scanf("%lld", &v);});
    std::for_each(value.begin(), value.end(), [](Long& v) {scanf("%lld", &v);});
    Long valueSum = std::accumulate(value.begin(), value.end(), 0);

    std::vector<Long> maxWeights(valueSum+1, INT64_MIN);
    maxWeights[0] = 0;
    for (int i = 0; i < n; ++i) {
        if (value[i] == 0) {
            maxWeights[i] += value[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = valueSum; j >= 0; --j) {
            if (maxWeights[j] != INT64_MIN && j+value[i] <= valueSum) {
                maxWeights[j+value[i]] = std::max(maxWeights[j+value[i]], maxWeights[j]+weight[i]);
            }
        }
    }

    int answer = 0;
    for (int i = 0; i <= valueSum; ++i) {
        if (w <= maxWeights[i]) {
            answer = i;
            break;
        }
    }

    printf("%d", answer);

    return 0;
}