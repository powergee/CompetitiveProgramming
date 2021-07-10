#include <iostream>
#include <algorithm>

bool inBetweenX(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> f) {
    int minX = std::min(a.second, b.second);
    int maxX = std::max(a.second, b.second);

    return minX < f.second && f.second < maxX && f.first == a.first;
}

bool inBetweenY(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> f) {
    int minY = std::min(a.first, b.first);
    int maxY = std::max(a.first, b.first);

    return minY < f.first && f.first < maxY && f.second == a.second;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        std::pair<int, int> a, b, f;
        scanf("%d %d", &a.first, &a.second);
        scanf("%d %d", &b.first, &b.second);
        scanf("%d %d", &f.first, &f.second);
        
        if (a.first == b.first && inBetweenX(a, b, f)) {
            printf("%d\n", std::abs(a.second - b.second) + 2);
        } else if (a.second == b.second && inBetweenY(a, b, f)) {
            printf("%d\n", std::abs(a.first - b.first) + 2);
        } else {
            printf("%d\n", std::abs(a.first - b.first) + std::abs(a.second - b.second));
        }
    }

    return 0;
}