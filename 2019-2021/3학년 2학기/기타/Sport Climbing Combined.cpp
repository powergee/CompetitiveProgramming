#include <iostream>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::tuple<int, int, int> players[n];
    for (int i = 0; i < n; ++i) {
        int num, p, q, r;
        scanf("%d %d %d %d", &num, &p, &q, &r);
        players[i] = std::make_tuple(p*q*r, p+q+r, num);
    }

    std::sort(players, players+n);

    for (int i = 0; i < 3; ++i) {
        auto[mult, sum, num] = players[i];
        printf("%d ", num);
    }

    return 0;
}