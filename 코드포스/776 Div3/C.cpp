#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

typedef long long Long;

struct Point {
    int w, x, i;
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        
        std::vector<Point> points(m);
        for (int i = 0; i < m; ++i) {
            int x, w;
            scanf("%d %d", &x, &w);
            points[i] = { w, x, i };
        }
        
        std::sort(points.begin(), points.end(), [](Point p1, Point p2) {
            return p1.w < p2.w;
        });
        std::sort(points.begin(), points.begin()+2*n, [](Point p1, Point p2) {
            return p1.x < p2.x;
        });

        int sum = 0;
        for (int i = 0; i < 2*n; ++i) {
            sum += points[i].w;
        }

        printf("%d\n", sum);
        for (int i = 0; i < n; ++i) {
            printf("%d %d\n", points[i].i+1, points[2*n-1-i].i+1);
        }
    }

    return 0;
}