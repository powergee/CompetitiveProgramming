#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> state(n), goal(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> state[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> goal[i];
    }

    std::vector<std::pair<int, int>> answer;
    int cargo = std::max_element(goal.begin(), goal.end()) - goal.begin();

    std::vector<int> toMove;
    for (int i = 0; i < n; ++i) {
        if (i != cargo && state[i] != 0) {
            toMove.emplace_back(state[i]);
        }
    }
    std::sort(toMove.begin(), toMove.end(), std::greater<>());
    
    for (int amount : toMove) {
        answer.emplace_back(cargo+1, amount);
    }

    for (int i = 0; i < n; ++i) {
        if (i != cargo && goal[i] > 0) {
            answer.emplace_back(i+1, goal[i]);
        }
    }

    std::cout << answer.size() << "\n";
    for (auto [i, x] : answer) {
        std::cout << "+ " << i << " " << x << "\n";
    }

    return 0;
}