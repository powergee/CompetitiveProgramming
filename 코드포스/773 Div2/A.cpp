#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        std::pair<int, int> points[3];
        int minY = INT32_MAX; 
        for (int i = 0; i < 3; ++i) {
            scanf("%d %d", &points[i].first, &points[i].second);
            minY = std::min(minY, points[i].second);
        }

        int length = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = i+1; j < 3; ++j) {
                if (points[i].second == points[j].second && points[i].second > minY) {
                    length = std::abs(points[i].first - points[j].first);
                }
            }
        }
        printf("%d\n", length);
    }
    
    return 0;
}