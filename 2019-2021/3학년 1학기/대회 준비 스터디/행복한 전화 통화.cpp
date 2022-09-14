#include <iostream>
#include <algorithm>

int main() {
    int n, m, _;
    std::pair<int, int> call[10000];
    std::pair<int, int> query;
    while (scanf("%d %d", &n, &m), n != 0 && m != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%d %d %d %d", &_, &_, &call[i].first, &call[i].second);
        }

        for (int i = 0; i < m; ++i) {
            scanf("%d %d", &query.first, &query.second);
            int answer = 0;
            for (int j = 0; j < n; ++j) {
                auto min = std::min(call[j], query);
                auto max = std::max(call[j], query);

                if (min.first + min.second - max.first >= 1) {
                    ++answer;
                }
            }
            printf("%d\n", answer);
        }
    }

    return 0;
}