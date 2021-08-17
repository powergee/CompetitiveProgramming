#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, l;
    scanf("%d %d", &n, &l);

    std::vector<std::pair<int, int>> holes;

    for (int i = 0; i < n; ++i) {
        int s, e;
        scanf("%d %d", &s, &e);
        holes.emplace_back(s, e);
    }

    std::sort(holes.begin(), holes.end());
    int lastFill = -1;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int fillStart = std::max(holes[i].first, lastFill+1);
        int fillEnd = holes[i].second;

        if (fillStart < fillEnd) {
            int length = fillEnd - fillStart;
            int count = (length / l) + ((length % l) ? 1 : 0);
            answer += count;

            lastFill = std::max(lastFill, fillStart + count*l-1);
        }
    }

    printf("%d", answer);

    return 0;
}