#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> changes(n*2);
    for (int i = 0; i < n; ++i) {
        int b, d;
        std::cin >> b >> d;
        changes[i*2] = { b, 1 };
        changes[i*2+1] = { d, -1 };
    }

    std::sort(changes.begin(), changes.end());
    int maxTime = -1, maxLives = 0, currLives = 0;
    for (auto [t, diff] : changes) {
        currLives += diff;
        if (maxLives < currLives) {
            maxLives = currLives;
            maxTime = t;
        }
    }

    std::cout << maxTime << " " << maxLives;

    return 0;
}