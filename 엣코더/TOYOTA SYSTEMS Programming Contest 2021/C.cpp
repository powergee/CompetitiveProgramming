#include <algorithm>
#include <cstdint>
#include <functional>
#include <cstdio>
#include <vector>
#include <iostream>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    std::vector<std::pair<int, int>> scores(n);
    for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < 3; ++j) {
            int single;
            scanf("%d", &single);
            sum += single;
        }
        scores[i] = {sum, i};
    }

    std::sort(scores.begin(), scores.end());
    std::vector<bool> answer(n);
    for (int i = 0; i < n; ++i) {
        int last = scores[i].first+300;
        auto found = std::upper_bound(scores.begin(), scores.end(), std::make_pair(last, INT32_MAX));
        if (scores.end()-found+1 <= k) {
            answer[scores[i].second] = true;
        } else {
            answer[scores[i].second] = false;
        }
    }

    for (int i = 0; i < n; ++i) {
        printf(answer[i] ? "Yes\n" : "No\n");
    }

    return 0;
}
