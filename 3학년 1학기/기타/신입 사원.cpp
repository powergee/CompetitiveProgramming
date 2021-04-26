#include <iostream>
#include <vector>
#include <algorithm>

std::pair<int, int> scores[100000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &scores[i].first, &scores[i].second);
        }

        std::sort(scores, scores+n);
        int answer = 1;
        int bThresh = scores[0].second;
        for (int i = 1; i < n; ++i) {
            if (scores[i].second < bThresh) {
                ++answer;
                bThresh = scores[i].second;
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}