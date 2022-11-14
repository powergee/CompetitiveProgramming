#include <iostream>
#include <functional>
#include <vector>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> piece(n);
    for (int i = 0; i < n; ++i) {
        int x, l;
        std::cin >> x >> l;
        piece[i] = { x, l };
    }
    std::sort(piece.begin(), piece.end());

    int answer = 1, reach = piece[0].first+piece[0].second;
    for (int i = 1; i < n; ++i) {
        if (reach < piece[i].first) {
            answer++;
        }
        reach = piece[i].first+piece[i].second;
    }
    std::cout << answer;

    return 0;
}