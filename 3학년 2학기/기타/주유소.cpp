#include <iostream>
#include <vector>

typedef long long Long;

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Long> dist(n, 0LL), price(n+1);
    for (int i = 1; i < n; ++i) {
        scanf("%lld", &dist[i]);
        dist[i] += dist[i-1];
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &price[i]);
    }

    std::vector<int> points;
    points.push_back(1);
    for (int i = 2; i <= n; ++i) {
        if (price[i] < price[points.back()]) {
            points.push_back(i);
        }
    }

    if (points.back() != n) {
        points.push_back(n);
    }

    Long result = 0;
    for (int i = 0; i < points.size()-1; ++i) {
        result += price[points[i]] * (dist[points[i+1]-1] - dist[points[i]-1]);
    }
    printf("%lld", result);

    return 0;
}