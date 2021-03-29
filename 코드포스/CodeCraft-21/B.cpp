#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, W;
        std::vector<int> blocks;
        scanf("%d %d", &N, &W);

        for (int i = 0; i < N; ++i) {
            int w;
            scanf("%d", &w);
            blocks.push_back(w);
        }

        std::sort(blocks.begin(), blocks.end(), std::greater<int>());
        std::multiset<int, std::greater<int>> lines;
        int filled = 0;

        for (int w : blocks) {
            auto found = lines.lower_bound(W-w);
            if (found == lines.end()) {
                lines.insert(w);
                ++filled;
            } else {
                int newLen = *found + w;
                lines.erase(found);
                if (newLen < W) {
                    lines.insert(newLen);
                }
            }
        }

        printf("%d\n", filled);
    }

    return 0;
}