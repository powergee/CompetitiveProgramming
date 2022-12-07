#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<int> interval(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> interval[i];
    }
    for (int i = 0; i < n; ++i) {
        int lower;
        std::cin >> lower;
        interval[i] -= lower;
    }

    int q;
    std::cin >> q;
    std::priority_queue<std::pair<int, int>> bird;
    for (int i = 0; i < q; ++i) {
        int size;
        std::cin >> size;
        bird.emplace(size, i);
    }

    std::vector<int> answer(q, n);
    for (int i = 0; i < n; ++i) {
        while (bird.size() && bird.top().first > interval[i]) {
            answer[bird.top().second] = i;
            bird.pop();
        }
    }

    for (int v : answer) {
        std::cout << v << "\n";
    }

    return 0;
}