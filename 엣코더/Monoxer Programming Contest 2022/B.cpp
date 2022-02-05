#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> pos {0};
    for (int i = 0; i < n; ++i) {
        int v;
        scanf("%d", &v);
        pos.push_back((pos.back()+v) % 360);
    }

    std::sort(pos.begin(), pos.end());
    int maxAngle = pos[0] + (360-pos.back());
    for (int i = 0; i < n; ++i) {
        maxAngle = std::max(maxAngle, pos[i+1] - pos[i]);
    }
    printf("%d", maxAngle);

    return 0;
}