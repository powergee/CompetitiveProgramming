#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int _, k;
    scanf("%d %d %d", &_, &_, &k);

    std::vector<std::pair<int, int>> points(k);
    std::vector<int> process;

    for (int i = 0; i < k; ++i) {
        scanf("%d %d", &points[i].first, &points[i].second);
    }

    std::sort(points.begin(), points.end());
    for (auto p : points) {
        auto found = std::lower_bound(process.begin(), process.end(), p.second, std::greater<int>());
        if (found == process.end()) {
            process.push_back(p.second);
        } else {
            *found = p.second;
        }
    }

    printf("%d", int(process.size()));
    
    return 0;
}