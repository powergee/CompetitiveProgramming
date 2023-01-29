// Solution of 비드맨 (BOJ 19590)
#include <algorithm>
#include <numeric>
#include <vector>

typedef long long Long;

Long greedyMatch(std::vector<Long>& arr) {
    Long sum = std::accumulate(arr.begin(), arr.end(), 0LL);
    Long max = *std::max_element(arr.begin(), arr.end());
    Long spare = sum - max;

    if (max < spare) {
        return sum % 2 == 0 ? 0LL : 1LL;
    } else {
        return max - spare;
    }
}
