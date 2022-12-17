#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    int left, right;
    std::cin >> left >> right;

    for (int i = 2; i < n; ++i) {
        int stone;
        std::cin >> stone;
        if (left <= right) {
            left += stone;
        } else {
            right += stone;
        }
    }

    int answer = 0;
    int diff = std::abs(left-right);
    for (int add : { 100, 50, 20, 10, 5, 2, 1 }) {
        if (diff >= add) {
            answer += diff / add;
            diff -= (diff / add) * add;
        }
    }

    std::cout << answer;

    return 0;
}