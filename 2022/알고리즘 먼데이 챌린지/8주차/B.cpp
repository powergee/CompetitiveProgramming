#include <iostream>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;

    std::vector<int> height(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> height[i];
    }

    std::vector<int> stack;
    for (int i = 0; i < n; ++i) {
        std::cout << stack.size() << " ";
        while (stack.size() && stack.back() <= height[i]) {
            stack.pop_back();
        }
        stack.push_back(height[i]);
    }

    return 0;
}